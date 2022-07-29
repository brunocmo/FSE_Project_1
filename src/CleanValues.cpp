#include <CleanValues.hpp>

void cleanUp(int sig) {
    digitalWrite(CRUZ_1_SEMAFORO_1_VERMELHO, LOW);
    digitalWrite(CRUZ_1_SEMAFORO_1_AMARELO, LOW);
    digitalWrite(CRUZ_1_SEMAFORO_1_VERDE, LOW);
    digitalWrite(CRUZ_1_SEMAFORO_2_VERMELHO, LOW);
    digitalWrite(CRUZ_1_SEMAFORO_2_AMARELO, LOW);
    digitalWrite(CRUZ_1_SEMAFORO_2_VERDE, LOW);
    pinMode(CRUZ_1_BUTTON_1, INPUT);
    pinMode(CRUZ_1_BUTTON_2, INPUT);
    pinMode(CRUZ_1_SENSOR_PASSAGEM_1, INPUT);
    pinMode(CRUZ_1_SENSOR_PASSAGEM_2, INPUT);
    pinMode(CRUZ_1_VELOCIDADE_1_A, INPUT);
    pinMode(CRUZ_1_VELOCIDADE_1_B, INPUT);
    pinMode(CRUZ_1_VELOCIDADE_2_A, INPUT);
    pinMode(CRUZ_1_VELOCIDADE_2_B, INPUT);
    pullUpDnControl(CRUZ_1_BUTTON_1,PUD_DOWN);
    pullUpDnControl(CRUZ_1_BUTTON_2,PUD_DOWN);
    pullUpDnControl(CRUZ_1_SENSOR_PASSAGEM_1,PUD_DOWN);
    pullUpDnControl(CRUZ_1_SENSOR_PASSAGEM_2,PUD_DOWN);
    pullUpDnControl(CRUZ_1_VELOCIDADE_1_A,PUD_DOWN);
    pullUpDnControl(CRUZ_1_VELOCIDADE_1_B,PUD_DOWN);
    pullUpDnControl(CRUZ_1_VELOCIDADE_2_A,PUD_DOWN);
    pullUpDnControl(CRUZ_1_VELOCIDADE_2_B,PUD_DOWN);

    // digitalWrite(CRUZ_2_SEMAFORO_1_VERMELHO, LOW);
    // digitalWrite(CRUZ_2_SEMAFORO_1_AMARELO, LOW);
    // digitalWrite(CRUZ_2_SEMAFORO_1_VERDE, LOW);
    // digitalWrite(CRUZ_2_SEMAFORO_2_VERMELHO, LOW);
    // digitalWrite(CRUZ_2_SEMAFORO_2_AMARELO, LOW);
    // digitalWrite(CRUZ_2_SEMAFORO_2_VERDE, LOW);
    // pinMode(CRUZ_2_BUTTON_1, INPUT);
    // pinMode(CRUZ_2_BUTTON_2, INPUT);
    // pinMode(CRUZ_2_SENSOR_PASSAGEM_1, INPUT);
    // pinMode(CRUZ_2_SENSOR_PASSAGEM_2, INPUT);
    // pinMode(CRUZ_2_VELOCIDADE_1_A, INPUT);
    // pinMode(CRUZ_2_VELOCIDADE_1_B, INPUT);
    // pinMode(CRUZ_2_VELOCIDADE_2_A, INPUT);
    // pinMode(CRUZ_2_VELOCIDADE_2_B, INPUT);
    // pullUpDnControl(CRUZ_2_BUTTON_1,PUD_DOWN);
    // pullUpDnControl(CRUZ_2_BUTTON_2,PUD_DOWN);
    // pullUpDnControl(CRUZ_2_SENSOR_PASSAGEM_1,PUD_DOWN);
    // pullUpDnControl(CRUZ_2_SENSOR_PASSAGEM_2,PUD_DOWN);
    // pullUpDnControl(CRUZ_2_VELOCIDADE_1_A,PUD_DOWN);
    // pullUpDnControl(CRUZ_2_VELOCIDADE_1_B,PUD_DOWN);
    // pullUpDnControl(CRUZ_2_VELOCIDADE_2_A,PUD_DOWN);
    // pullUpDnControl(CRUZ_2_VELOCIDADE_2_B,PUD_DOWN);

    delay(1);

    std::cout << '\n' << "Limpeza da placa feita!" << '\n';

    exit(0);
}