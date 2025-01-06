#pragma once

#include <iostream>
//{{{ catalyst
/*
#include "sph/particles_data.hpp"
#ifdef SPH_EXA_USE_CATALYST2
#include "catalyst_adaptor.h"
#endif
*/
//}}}
#ifdef _WITH_ASCENT
#include "ascent_adaptor.h"
#endif

namespace viz
{

//{{{ init_catalyst
/*
void init_catalyst([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#ifdef SPH_EXA_USE_CATALYST2
    CatalystAdaptor::Initialize(argc, argv);
    std::cout << "CatalystInitialize\n";
#endif
}
*/
//}}}

//{{{ init_ascent
//template<class DataType>
//void init_ascent([[maybe_unused]] DataType& d, [[maybe_unused]] long startIndex)
void init_ascent()
{
#ifdef _WITH_ASCENT
    std::cout << "AscentInitialize begin\n";
    AscentAdaptor::Initialize();
    //AscentAdaptor::Initialize(d, startIndex);
    std::cout << "AscentInitialize end\n";
#endif
}
//}}}

//{{{ execute
void execute(
        [[maybe_unused]] JDataArrays& arrays2,
        //[[maybe_unused]] long endIndex,
        [[maybe_unused]] double TimeStep)
{
#ifdef _WITH_ASCENT
    AscentAdaptor::Execute(arrays2, TimeStep);
    //AscentAdaptor::Execute(d, startIndex, endIndex);
#endif
}
//todo template<class DataType>
//todo void execute([[maybe_unused]] DataType& d, [[maybe_unused]] long startIndex, [[maybe_unused]] long endIndex)
//todo {
//todo /*    
//todo #ifdef SPH_EXA_USE_CATALYST2
//todo     CatalystAdaptor::Execute(d, startIndex, endIndex);
//todo #endif
//todo */
//todo #ifdef _WITH_ASCENT
//todo     AscentAdaptor::Execute(d, startIndex, endIndex);
//todo #endif
//todo }
//}}}

//{{{ finalize
void finalize()
{
/*    
#ifdef SPH_EXA_USE_CATALYST2
    CatalystAdaptor::Finalize();
#endif
*/
#ifdef _WITH_ASCENT
    AscentAdaptor::Finalize();
#endif
}
//}}}

} // namespace viz
