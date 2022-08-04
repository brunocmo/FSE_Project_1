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
                sendValuestoServer(cruzamento->numberPassedRedPrincipal);
                sendValuestoServer(cruzamento->numberPassedRedAuxiliar);
                sendValuestoServer(cruzamento->numberPassedVelocityLimitPrincipal);
                sendValuestoServer(cruzamento->numberPassedVelocityLimitAuxiliar);
                receiveValuestoServer();

                if( clientSemaphore->numberReceived == 1 )
                    cruzamento->changeState(6);
                if( clientSemaphore->numberReceived == 2 )
                    cruzamento->changeState(8);
                if( clientSemaphore->numberReceived == 3 )
                    cruzamento->changeState(5);


            
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

void DistrictControl::receiveValuestoServer() {    
    if(clientSemaphore->recvFromServer()) {
        std::cout << "Erro ao enviar valores para o servidor!" << '\n';
    }
}