#include "IO_Manager.h"

IO_Manager::IO_Manager(std::string file_name, IO_Manager_Mode mode) {
    this->file_name = file_name;
    this->mode = mode;
    switch (mode) {
    case read_binary:
        file.open(file_name, std::ios::in | std::ios::binary); // if file is already exist open it in read binary mode
        if (!file.is_open()) {
            //create file, write file_header in the begining and open it in a read mode
            file.open(file_name, std::ios::out | std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "error: unable to create file in read_binary mode" << std::endl;
                break;
            }
            file.close();
            //open created file in a read binary mode
            file.open(file_name, std::ios::in | std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "error: unable to open file in a read_binary mode" << std::endl;
                break;
            }
        }
        break;
    case append_binary:
        file.open(file_name, std::ios::app | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "error: unable to create file in append_binary mode" << std::endl;
            break;
        }
        break;
    }
}

IO_Manager::~IO_Manager(void) {
    if (file.is_open()) {
        file.close();
    }
}

void IO_Manager::append_req(Req req) {
    if (mode == read_binary) {
        std::cerr << "error: forbidden to write in read_binary mode" << std::endl;
    }
    else {
        time_l  tm = req.time.get_val();
        mem_rep ad = req.addr.get_val();
        file.write(reinterpret_cast<char *>(&tm), sizeof(time_l));
        file.write(reinterpret_cast<char *>(&ad), sizeof(mem_rep));
        file.write(reinterpret_cast<char *>(&req.size), sizeof(req_size));
        unsigned char tp = static_cast<unsigned char>(req.type);
        file.write(reinterpret_cast<char *>(&tp), sizeof(unsigned char));
    }
}

void IO_Manager::append_req(time_l time, mem_rep addr, req_size size, req_type type) {
    if (mode == read_binary) {
        std::cerr << "error: forbidden to write in read_binary mode" << std::endl;
    }
    else {
        file.write(reinterpret_cast<char *>(&time), sizeof(time_l));
        file.write(reinterpret_cast<char *>(&addr), sizeof(mem_rep));
        file.write(reinterpret_cast<char *>(&size), sizeof(req_size));
        unsigned char tp = static_cast<unsigned char>(type);
        file.write(reinterpret_cast<char *>(&tp), sizeof(unsigned char));
    }
}

Req* IO_Manager::read_next_req() {
    if (mode == append_binary) {
        std::cerr << "error: forbidden to read in append_binary mode" << std::endl;
    }
    else {
        if (file.eof()) {
            return nullptr;
        }
        time_l time;
        mem_rep addr;
        req_size size;
        unsigned char type;
        file.read(reinterpret_cast<char*>(&time), sizeof(time_l));
        if (file.eof()) {
            return nullptr;
        }
        file.read(reinterpret_cast<char*>(&addr), sizeof(mem_rep));
        file.read(reinterpret_cast<char*>(&size), sizeof(req_size));
        file.read(reinterpret_cast<char*>(&type), sizeof(unsigned char));
        return new Req(time, addr, size, static_cast<req_type>(type));
    }
    return nullptr;
}

void IO_Manager::save_file() {
    file.close();
}

IO_Manager_Mode IO_Manager::get_mode() {
    return this->mode;
}