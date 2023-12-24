// 1D solver:
#include <vector>
#include <iostream>
#include <cassert>
// make user input later
//

class Matrix //class to keep matrix contiguous as opposed to vec of vec on stack
{
    private:
    int m_length{};
    int m_iLength{};
    int m_jLength{};
    std::vector<double> m_data{};


    public:
    Matrix(int iLength, int jLength)
    : m_iLength{iLength}
    , m_jLength{jLength} //later could make generic tensor with parameter pack + templates
    , m_data(iLength * jLength)
    {
        m_length = m_iLength * m_jLength;
    }

    Matrix operator*();
    Matrix operator+(Matrix matrix);
    double& operator()(int i, int j);
};
double& Matrix::operator()(int i, int j)
{
    assert(i < m_iLength && "i subscript out of range");
    assert(j < m_jLength && "j subscript out of range");
    return m_data[i + j * m_iLength];
}
Matrix Matrix::operator+()
{

}


void solve()
{
    //#SETUP
    // set default states (make user input later)
    //##GRIDDING
    int gridDim{10};
    double domainLength{10};
    double gridCellLength{domainLength / gridDim}; // will make property of class grid later if needed
    double timestep{1}; // needs time step for each variable later
    double courant{timestep / gridCellLength};
    //##INITIAL VALUES
    double initialFlowValue{20};
    std::vector<double> initialVelocities(gridDim, initialFlowValue);
    Matrix velocities{initialVelocities};
    Matrix velocitiesNext{initialVelocities};// could combine into struct for contiguity



    
    //#SOLVE
    //Burgers equation, non - conservative form
    double boundaryCondition{initialFlowValue};
    int temporalIndex{1};
    bool isConverge{false};
    while (!isConverge)
    {
        for (auto i{0}; i < gridDim; ++i)
        {
            if (i == 0)
            {
                velocitiesNext[i] = boundaryCondition;
                continue;
            }
            velocitiesNext[i] = -courant * (velocities[i] * (velocities[i-1] - velocities[i])) + velocities[i]; 
            if (i == gridDim - 1) // careful prescedence here 
            {}
            // could save memory by having only 1 vel vector and iterating backwards
        }
        temporalIndex++;
    }
    //bool isConverge{false};
    //while (!isConverge)
    //{
    //    
    //}

}


