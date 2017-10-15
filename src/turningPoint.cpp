#include "turningPoint.h"

turningPoint::turningPoint()
{
    //0 = North, 1 = East, 2 = South, 3 = West
}

Orientation turningPoint::getNewOrientation(Orientation _currentOrientation)
{
    Orientation result;

    int numberOfElementsPreDelete=m_availableOrientations.size();
    if(numberOfElementsPreDelete > 1)
    {
        deleteCurrentOrientation(_currentOrientation);
    }

    int numberOfElements=m_availableOrientations.size();
    if(numberOfElements>0)
    {
        int randomSelection=rand() % numberOfElements;
        result=m_availableOrientations[randomSelection];
    }
    else
    {
        //default
        result=EAST;
    }

    //need to push back deleted value now orientation has been collected
    m_availableOrientations.push_back(_currentOrientation);

    return result;
}

void turningPoint::deleteCurrentOrientation(Orientation _currentOrientation)
{
    int numberOfElements=m_availableOrientations.size();
    for(int i=0; i<numberOfElements; i++)
    {
        if(m_availableOrientations[i]==_currentOrientation)
        {
            m_availableOrientations.erase(m_availableOrientations.begin()+i);
            break;
        }
    }
}
