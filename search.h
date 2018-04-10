#ifndef SEARCH_H
#define SEARCH_H
#include "individual.h"

class Search
{
public:
    Search();
    Individual apply(Problem* problem, Individual individual);
};

#endif // SEARCH_H
