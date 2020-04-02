//
// Created by 佘崧林 on 2020/4/2.
//

#ifndef KEYMININGALGORITHM_DISPLAYMAP_H
#define KEYMININGALGORITHM_DISPLAYMAP_H

#include <string>

class DisplayMap {
protected:
    std::string **string_map;
    uint row = 1, column = 1;
    const std::string default_string = "  ";
public:
    DisplayMap(std::string default_string = "0");
    DisplayMap(uint r, uint c, std::string dflt = "  ");
    DisplayMap(const DisplayMap& dm);
    ~DisplayMap();
    uint get_row_size()const{ return this->row; }
    uint get_column_size()const{ return this->column; }
    void resize(uint r, uint c);
    void set_map_node(uint r, uint c, std::string data){ this->string_map[r][c] = data; }
    void set_map_row(uint r, std::string str);
    void set_map_column(uint c, std::string str);
    void set_sub_area(uint x, uint y, DisplayMap* submap); // x,y is the left upper point
    operator std::string()const;
};

#import "./DisplayMap.tpp"

#endif //KEYMININGALGORITHM_DISPLAYMAP_H
