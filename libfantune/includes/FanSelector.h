//
// Created by semoro on 15.07.16.
//

#ifndef FANTUNE_FANSELECTOR_H
#define FANTUNE_FANSELECTOR_H

#include <vector>
#include <fstream>
#include "Fan.h"

class FanSelector {

public:
    std::vector<Fan *> detectFans();

    std::vector<Fan *> loadFans(std::fstream &file);

};

#endif //FANTUNE_FANSELECTOR_H
