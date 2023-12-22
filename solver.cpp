// 1D solver:
#include <vector>
// make user input later

void solve()
{
    //setup
    int gridDim{10};
    std::vector<double> flowState(gridDim);
    flowState.resize(gridDim);

    // set default states (make user input later)
    // choose distribution ( should really just be choose boundaries and let converge)
    double initialValue{20};
    std::vector<double> initialFlowState(gridDim, initialValue);

    


    //Solve


}

