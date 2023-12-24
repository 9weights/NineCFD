// 1D solver:
#include <vector>
#include <iostream>
#include <cassert>
// make user input later
//

class Matrix //class to keep matrix contiguous as opposed to vec of vec on stack, can template later
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
    Matrix(const std::vector<double>& data, int jLength) // might make seperate class
    : m_iLength{static_cast<int>(data.size())}
    , m_jLength{jLength}
    {
        this->initialiseData(data);
        m_length = m_iLength * m_jLength;
    }

    Matrix operator*();
    Matrix operator+(Matrix matrix);
    double& operator()(int i, int j)
    {
        assert(i >= 0 && i < m_iLength && "i subscript out of range");
        assert(j >= 0 && j < m_jLength && "j subscript out of range");
        return m_data[i + j * m_iLength];
    }
    void initialiseData(const std::vector<double>& data)
    {
        assert(static_cast<int>(data.size()) == m_iLength && "vector size mismatch");
        for (auto i{0}; i < m_iLength; ++i)
        {
            (*this)(i,0) = data[i];// may have runtime conversion error here
        }
    }
    void resize()
    {

    }
};

void solve()
{
    //#SETUP
    // set default states (make user input later)
    //##GRIDDING
    int gridCount{10};
    double domainLength{10};
    double gridCellLength{domainLength / gridCount}; // will make property of class grid later if needed
    double timestep{1}; // needs time step for each variable later
    double courant{timestep / gridCellLength};
    //##INITIAL VALUES
    double initialFlowValue{20};
    std::vector<double> initialVelocities(gridCount, initialFlowValue);
    Matrix velocities{initialVelocities, 100};



    
    //#SOLVE
    //Burgers equation, non - conservative form
    double boundaryCondition{initialFlowValue};
    int temporalIndex{1};
    bool isConverge{false};
    std::vector<double> residuals(gridCount);
    while (!isConverge)
    {
        for (auto i{0}; i < gridCount; ++i)
        {
            if (i == 0)
            {
                velocities(i,temporalIndex) = boundaryCondition;
                continue;
            }
            velocities(i,temporalIndex) =
                -courant * (velocities(i,temporalIndex) 
                * (velocities(i,temporalIndex) - velocities(i - 1,temporalIndex)))
                + velocities(i,temporalIndex); 
            residuals[i] = velocities(i,temporalIndex) - velocites(i, temporalIndex - 1);
            // could save memory by having only 1 vel vector and iterating backwards
        }
        //##CHECK CONVERGENCE
        for (auto residual : residuals)
        {
            residualSum += residual;
        }
        residualMean = residualSum / gridCount;
        temporalIndex++;
    }
    //bool isConverge{false};
    //while (!isConverge)
    //{
    //    
    //}

}


