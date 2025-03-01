#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <stdio.h>
#include <fstream>
#include <cmath>



class particle{
    public:
        double mass = 0;
        std::vector<double> Position = {0,0,0};
        //Forces on X/Y/Z values
        std::vector<double> forces = {0,0,0};
        //Velocities on X/Y/Z values.
        std::vector<double> velocities = {0,0,0};
        
};

void calcForces(std::vector<particle>& pv, size_t size){
    /* TODO:
    *   Compute the gravitational force between two objects of class particle.
    *   Sum force vectors for each particle
    *   Reset Forces to zero at the start of each step/call.
    */
   //I can use a double loop to loop through all possible calculations of particles.
   const double G = (6.674 * pow(10,-11));
   double dX = 0;
   double dY = 0;
   double dZ = 0;
   double dist = 0;
   for(size_t p1 = 0; p1 < size; p1++){
    //std::cout <<"break Loop 1 Start"<<std::endl;
    pv[p1].forces[0] = 0;
    pv[p1].forces[1] = 0;
    pv[p1].forces[2] = 0;
    for(size_t p2 = 0; p2 < size; p2++){
        if(p1 != p2){
            //std::cout <<"break Loop 2 Start"<<std::endl;
            dX = pv[p2].Position[0] - pv[p1].Position[0];
            dY = pv[p2].Position[1] - pv[p1].Position[1];
            dZ = pv[p2].Position[2] - pv[p1].Position[2];
            //std::cout << "X, Y, and Z distances"<< dX << " " << dY << " " << dZ << std::endl;
            dist = std::sqrt(dX * dX + dY * dY + dZ * dZ);
            //std::cout << "Total Distance " << dist << std::endl; 
            //td::cout << "First Half Equation: " << (dX / dist) << std::endl;
            pv[p1].forces[0] += (dX / dist)*(G * ((pv[p1].mass * pv[p2].mass)/pow(dist,2) + 0.01));
            pv[p1].forces[1] += (dY / dist)*(G * ((pv[p1].mass * pv[p2].mass)/pow(dist,2) + 0.01));
            pv[p1].forces[2] += (dZ / dist)*(G * ((pv[p1].mass * pv[p2].mass)/pow(dist,2) + 0.01));
            //std::cout << "X, Y, and Z Forces " << pv[p1].forces[0] << " " << pv[p1].forces[1] << " " << pv[p1].forces[2] << std::endl;
        }
    }
    
    //std::cout <<"break Loop 2 End"<<std::endl;
   }
   //std::cout <<"break Loop 1 End"<<std::endl;
   /*std::cout << pv[0].mass << " " 
   << pv[0].Position[0] << " " 
   << pv[0].Position[1] << " " 
   << pv[0].Position[2] << " " 
   << pv[0].forces[0] << " " 
   << pv[0].forces[1] << " " 
   << pv[0].forces[2] << " " 
   << pv[0].velocities[0] << " " 
   << pv[0].velocities[1] << " " 
   << pv[0].velocities[2] << " " << std::endl;*/

}

void fileLoad(){
    //Load data from a file.
    //I... don't really know how exactly to do this (Not that I don't know how to read from a file, just don't know... when?)
}

void writeFile(std::vector<particle>& p, size_t size){
    //Code commented out to avoid issues with testing in Centaurus.
    /*std::ofstream tsvFile("data.tsv");
    tsvFile.open("data.tsv");
    if(tsvFile.is_open()){
        std::cout << "File Opened Sucessfully" << std::endl;
        for (size_t i = 0; i < size; ++i) {
            if (i < size - 1) {
                 tsvFile << "\t";
            }
        }
        
        std::cout << std::endl;

    } else{
        std::cout << "Uh oh! Error Here! Hey! There's a Error Here! LOOK. LOOK AT THIS ERROR ITS SO ERRORY!" << std::endl;
    }
    tsvFile.close();
    */
}

void newRandomParticle(std::vector<particle>& P, size_t ID){
    //Creates object of class particle with randomized mass, position, and velocity.
    P[ID].mass = rand() % 1000000 + 1;
    P[ID].Position = {double(rand() % 1000000 + 1), ((double)(rand() % 10000000 + 1)), ((double)(rand() % 10000000 + 1))};
    P[ID].velocities = {double(rand() % 1000000 + 1), ((double)(rand() % 10000000 + 1)), ((double)(rand() % 10000000 + 1))};
    
    /*td::cout << P[ID].mass << "     " 
    << P[ID].Position[0] << "     " 
    << P[ID].Position[1] << "     " 
    << P[ID].Position[2] << "     " 
    << P[ID].forces[0] << "     " 
    << P[ID].forces[1] << "     " 
    << P[ID].forces[2] << "     " 
    << P[ID].velocities[0] << "     " 
    << P[ID].velocities[1] << "     " 
    << P[ID].velocities[2] << "     ";*/
}


void updateVelocity(std::vector<particle>& pv, size_t size, double tStep){
    double aX = 0;
    double aY = 0;
    double aZ = 0;
    for(size_t i = 0; i < size; i ++){
        aX = pv[i].forces[0] / pv[i].mass;
        aY = pv[i].forces[1] / pv[i].mass;
        aZ = pv[i].forces[2] / pv[i].mass;
        //std::cout <<"break 1"<<std::endl;
        pv[i].velocities[0] = pv[i].velocities[0] + aX * tStep;
        pv[i].velocities[1] = pv[i].velocities[1] + aY * tStep;
        pv[i].velocities[2] = pv[i].velocities[2] + aZ * tStep;
        //std::cout <<"break 2"<<std::endl;
    }
    /*std::cout << pv[0].mass << " " 
    << pv[0].Position[0] << " " 
    << pv[0].Position[1] << " " 
    << pv[0].Position[2] << " " 
    << pv[0].forces[0] << " " 
    << pv[0].forces[1] << " " 
    << pv[0].forces[2] << " " 
    << pv[0].velocities[0] << " " 
    << pv[0].velocities[1] << " " 
    << pv[0].velocities[2] << " " << std::endl;*/
    //TODO: Update particle velocities based on forces and masses of particle.
}

void updatePosition(std::vector<particle>& pv, size_t size, double tStep){
    //TODO: Update Particle positions based on velocities and time step.
    //0 is X position, 1 is Y position.
    for(size_t i = 0; i < size; i ++){
        //std::cout <<"break Loop Increment"<<std::endl;
        pv[i].Position[0] = pv[i].Position[0] + pv[i].velocities[0] * tStep;
        pv[i].Position[1] = pv[i].Position[1] + pv[i].velocities[1] * tStep;
        pv[i].Position[2] = pv[i].Position[2] + pv[i].velocities[2] * tStep;
    }
    //std::cout <<"break End Loop"<<std::endl;
    /*std::cout << pv[0].mass << " " 
    << pv[0].Position[0] << " " 
    << pv[0].Position[1] << " " 
    << pv[0].Position[2] << " " 
    << pv[0].forces[0] << " " 
    << pv[0].forces[1] << " " 
    << pv[0].forces[2] << " " 
    << pv[0].velocities[0] << " " 
    << pv[0].velocities[1] << " " 
    << pv[0].velocities[2] << " " << std::endl;*/
}


//Command Line Arguments: Number of Particles, Time Step Size (deltaT), Iteration count, how often to dump state.
int main(int argc, char* argv[]){
    /*I know srand isn't the best option here, I am still looking into
    * the way you recommended to me from the feedback on the merge assignment ^-^
    */
    srand(time(NULL));
    std::vector<particle> bodies;
    size_t bodyCount = std::atof(argv[1]);
    int loopSize = std::atof(argv[2]);
    int timeLoops = std::atof(argv[3]);
    int stateDump = std::atof(argv[4]);
    int nextDump = stateDump;
    std::cout << "Particle Count: " << bodyCount << "\nLoop Increments: " << loopSize
    << "\nTotal Loops: "<< timeLoops << "\nDumps Every " << stateDump << " loops." << std::endl;

    //The variable name is rather morbid, but its kinda funny so I'm keeping it.
    std::cout << "Randomizing Particles..." << std::endl;
    for(size_t i = 0; i < bodyCount; i++){
        //std::cout << "Current Particle being Created: " << i << std::endl;
        bodies.push_back(particle());
        newRandomParticle(bodies, i);
    }
    std::cout << "Starting calculations..." << std::endl;
    double sTime = time(NULL);
    for(double i = 0; i < timeLoops; i += loopSize){
        calcForces(bodies, bodyCount);
        //std::cout << "Updating Velocity" << std::endl;
        updateVelocity(bodies, bodyCount, i);
        //std::cout << "Updating Positions" << std::endl;
        updatePosition(bodies, bodyCount, i);
      
        if(i >= nextDump){
            std::cout << "Dumping Data..."<< std::endl;
            //This sets the next time to dump the state to the correct timing.
            nextDump += stateDump;
            //Was unable to get the Read/Write functions working as intended,
            //Will go into office hours to better understand the concept.
            //writeFile(bodies, bodyCount);
        }
    }
    double eTime = time(NULL);

    std::cout << "Time Taken to simulate: " << eTime - sTime << " Seconds." << std::endl;
}