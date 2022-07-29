#include <DistrictControl.hpp>

DistrictControl::DistrictControl() {
    signal(SIGINT, cleanUp);
    signal(SIGTERM, cleanUp);
    signal(SIGHUP, cleanUp);

}

DistrictControl::~DistrictControl() = default;

void DistrictControl::start() {
    while(1) {

        cruzamento1.sensores->receiveSensors();
        cruzamento1.pedestres->receiveMessage();
        cruzamento1.controle();

        if(twoSeconds > 1) {
        twoSeconds = -1;

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
        }

        twoSeconds++;
        
        sleep(1);
    }

}