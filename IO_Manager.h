#pragma once
#include <string>
#include <fstream>
#include "Req.h"

typedef enum { read_binary, append_binary } IO_Manager_Mode;

/**
* IO_Manager stores information in a binary file in in accordance with the following rules:
*  - Information about type of the Req is stored in the end of the record in 1 byte.
*  - Binary file has the following structure:
*    | /record/ | ... | /record/ | 
*/
class IO_Manager {
public:
    IO_Manager(std::string file_name, IO_Manager_Mode mode = read_binary);
    ~IO_Manager(void);
    
    /**
    * Record Req in the end of the output file.
    */
    void append_req(Req req);  
    
    /** 
    * Record Req in the end of the output file.
    */
    void append_req(time_l time, mem_rep addr, req_size size, req_type type); 

    /**
    * Read the next record with information about Req.
    * Return Req object in successful read otherwise null.
    */
    Req* read_next_req();

    /**
    * Return mode of the current instance of IO_Manager
    */
    IO_Manager_Mode get_mode();
private:
    std::string      file_name;
    std::fstream     file;
    IO_Manager_Mode  mode;   

    /**
    * Save changes to binary file in accordance with the above rules.
    */
    void save_file();
};