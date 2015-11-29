#include "mbed-drivers/mbed.h"

using mbed::util::FunctionPointer1;
using mbed::util::FunctionPointerBind;
using mbed::util::Event;

static DigitalOut led(LED1);

static void blinky(int i) {
    led = i;
}

void app_start(int, char**) {
    FunctionPointer1<void, int> ptr_to_blinky(blinky); // 関数へのポインターの生成
    FunctionPointerBind<void> bind_of_blinky_0(ptr_to_blinky.bind(0)); // 引数(0)をbind
    FunctionPointerBind<void> bind_of_blinky_1(ptr_to_blinky.bind(1)); // 引数(1)をbind
    Event e_0(bind_of_blinky_0); // LEDを消すイベントを生成
    Event e_1(bind_of_blinky_1); // LEDを光らせるイベントを生成
    minar::Scheduler::postCallback(e_0).period(minar::milliseconds(2000)); // 2秒ごとに実行
    minar::Scheduler::postCallback(e_1).delay(minar::milliseconds(1000)).period(minar::milliseconds(2000)); // 1秒後から2秒ごとに実行
}
