#include <DistrictControl.hpp>

DistrictControl::DistrictControl( bool isThisFirstCrossRoad, std::string serverAddr, int portAddr ) {
    signal(SIGINT, cleanUp);
    signal(SIGTERM, cleanUp);
    signal(SIGHUP, cleanUp);

    counterSeconds = 0;
    twoSeconds = 0;
    sumVelocity = 0;
    checkThisFirstCrossRoad = isThisFirstCrossRoad;

    firstDistritc = checkThisFirstCrossRoad;

    cruzamento = new CrossroadControl( checkThisFirstCrossRoad );

    clientSemaphore = new Client(serverAddr, portAddr);
}

DistrictControl::~DistrictControl() {
    delete cruzamento;
    delete clientSemaphore;
}

void DistrictControl::start() {
    while(1) {

        cruzamento->sensores->receiveSensors();
        cruzamento->pedestres->receiveMessage();
        cruzamento->controle();

        if(twoSeconds > 2) {

            twoSeconds = -1;

        if(!velocityVehiclesPrincipal.empty()) {
            sumVelocity = 0;
            for( int veloc : velocityVehiclesPrincipal) sumVelocity+=veloc;
            sumVelocity/=int(velocityVehiclesPrincipal.size());
            sendValuestoServer(sumVelocity);
            } else sendValuestoServer(-1);

            if(!velocityVehiclesAuxiliar.empty()) {
            sumVelocity = 0;
            for( int veloc : velocityVehiclesAuxiliar) sumVelocity+=veloc;
            sumVelocity/=int(velocityVehiclesAuxiliar.size());
            sendValuestoServer(sumVelocity);
            } else sendValuestoServer(-1);


            sendValuestoServer(carsPerMinute(cruzamento->sensores->getCarsNumberPassageUp()));
            sendValuestoServer(carsPerMinute(cruzamento->sensores->getCarsNumberPassageLeft()));
            sendValuestoServer(carsPerMinute(cruzamento->sensores->getCarsNumberPassageDown()));
            sendValuestoServer(carsPerMinute(cruzamento->sensores->getCarsNumberPassageRight()));
        }

        twoSeconds++;
        counterSeconds++;
        
        sleep(1);
    }

}

int DistrictControl::carsPerMinute(int numberOfCars) {
    return int(float(numberOfCars)/float(counterSeconds)*60.0f);
}

void DistrictControl::sendValuestoServer(int valuetoSend) {
    
    if(clientSemaphore->sendToServer(valuetoSend)) {
        std::cout << "Erro ao enviar valores para o servidor!" << '\n';
    }

}