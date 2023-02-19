#include "dshot.h"

/* Functions */
extern "C" {
    void dshot_init(dshot_type_e dshot_type);
    void dshot_write(uint16_t* motor_value);
}

static const uint32_t FREQUENCY = 8000;

static uint32_t count;

static void run(const uint32_t usec)
{
    static uint32_t prev;

    if (usec-prev > 1000000/FREQUENCY) {
        count++;
        prev = usec;
        static bool ready;
        uint16_t motorvals_init[4] = {47, 47, 47, 47};
        uint16_t motorvals[4] = {48, 48, 48, 48};
        dshot_write(ready ? motorvals : motorvals_init);
        ready  = true;
    }
}

void setup(void)
{
    Serial.begin(115200);

    pinMode(PB3, OUTPUT);
    pinMode(PB4, OUTPUT);
    pinMode(PB6, OUTPUT);
    pinMode(PB7, OUTPUT);

    dshot_init(DSHOT600);
}


void loop(void)
{
    const auto usec = micros();

    run(usec);

    Serial.println(count);
}
