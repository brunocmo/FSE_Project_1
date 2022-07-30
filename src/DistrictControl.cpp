#include <DistrictControl.hpp>

DistrictControl::DistrictControl() {
    signal(SIGINT, cleanUp);
    signal(SIGTERM, cleanUp);
    signal(SIGHUP, cleanUp);

    counterSeconds = 0;
}

DistrictControl::~DistrictControl() = default;

void DistrictControl::start() {



    while(1) {

        cruzamento1.sensores->receiveSensors();
        cruzamento1.pedestres->receiveMessage();
        cruzamento1.controle();

        if(twoSeconds > 4) {
            twoSeconds = -1;

            std::cout << "===========================================" << '\n';

            if(!velocityVehiclesPrincipal.empty()) {
            sumVelocity = 0;
            for( int veloc : velocityVehiclesPrincipal) sumVelocity+=veloc;
            sumVelocity/=int(velocityVehiclesPrincipal.size());
            std::cout << "A velocidade média da via Principal é de " << sumVelocity << " km/h" <<'\n';
            } else std::cout << "Sem veículos na via Principal" << '\n';

            if(!velocityVehiclesAuxiliar.empty()) {
            sumVelocity = 0;
            for( int veloc : velocityVehiclesAuxiliar) sumVelocity+=veloc;
            sumVelocity/=int(velocityVehiclesAuxiliar.size());
            
            std::cout << "A velocidade média da via Auxiliar é de " << sumVelocity << " km/h" <<'\n';
            } else std::cout << "Sem veículos na via Auxiliar" << '\n';

            std::cout << 
                "Passaram " << 
                carsPerMinute(cruzamento1.sensores->getCarsNumberPassageUp()) <<
                " carros/min no sentido ↑" << 
            '\n';

            std::cout << 
                "Passaram " << 
                carsPerMinute(cruzamento1.sensores->getCarsNumberPassageLeft()) <<
                " carros/min no sentido ←" << 
            '\n';

            std::cout << 
                "Passaram " << 
                carsPerMinute(cruzamento1.sensores->getCarsNumberPassageDown()) <<
                " carros/min no sentido ↓" << 
            '\n';

            std::cout << 
                "Passaram " << 
                carsPerMinute(cruzamento1.sensores->getCarsNumberPassageRight()) <<
                " carros/min no sentido →" << 
            '\n';

            std::cout << "===========================================" << '\n';
        }

        twoSeconds++;
        counterSeconds++;
        
        sleep(1);
    }

}

int DistrictControl::carsPerMinute(int numberOfCars) {
    return int(float(numberOfCars)/float(counterSeconds)*60.0f);
}