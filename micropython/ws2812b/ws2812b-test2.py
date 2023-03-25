from machine import Pin
import array, time
from machine import Pin
import rp2




p24 = Pin(24, Pin.IN, Pin.PULL_UP)
print(p24.value())

p25 = Pin(25, Pin.OUT)


# Configure the number of WS2812 LEDs.
NUM_LEDS = 1


@rp2.asm_pio(
    sideset_init=rp2.PIO.OUT_LOW,
    out_shiftdir=rp2.PIO.SHIFT_LEFT,
    autopull=True,
    pull_thresh=24,
)
def ws2812():
    # fmt: off
    T1 = 2
    T2 = 5
    T3 = 3
    wrap_target()
    label("bitloop")
    out(x, 1)               .side(0)    [T3 - 1]
    jmp(not_x, "do_zero")   .side(1)    [T1 - 1]
    jmp("bitloop")          .side(1)    [T2 - 1]
    label("do_zero")
    nop()                   .side(0)    [T2 - 1]
    wrap()
    # fmt: on


# Create the StateMachine with the ws2812 program, outputting on Pin(22).
sm = rp2.StateMachine(0, ws2812, freq=8_000_000, sideset_base=Pin(23))

# Start the StateMachine, it will wait for data on its FIFO.
sm.active(1)

# Display a pattern on the LEDs via an array of LED RGB values.
ar = array.array("I", [0 for _ in range(NUM_LEDS)])

# Cycle colours.
for i in range(4 * NUM_LEDS):
    for j in range(NUM_LEDS):
        r = 100
        g = 0
        b = 0
        ar[j] = g << 16 | r<<8| b
    sm.put(ar, 8)
    time.sleep_ms(50)
for i in range(4 * NUM_LEDS):
    for j in range(NUM_LEDS):
        r = 0
        g = 100
        b = 0
        ar[j] = g << 16 | r<<8| b
    sm.put(ar, 8)
    time.sleep_ms(50)
for i in range(4 * NUM_LEDS):
    for j in range(NUM_LEDS):
        r = 0
        g = 0
        b = 100
        ar[j] = g << 16 | r<<8| b
    sm.put(ar, 8)
    time.sleep_ms(50)
for i in range(4 * NUM_LEDS):
    for j in range(NUM_LEDS):
        r = 100
        g = 100
        b = 100
        ar[j] = g << 16 | r<<8| b
    sm.put(ar, 8)
    time.sleep_ms(50)
for i in range(4 * NUM_LEDS):
    for j in range(NUM_LEDS):
        r = 0
        g = 0
        b = 0
        ar[j] = g << 16 | r<<8| b
    sm.put(ar, 8)
    time.sleep_ms(50)

while 1:
    if p24.value()==0:
        p25.on()
    else:
        p25.off()
        



            
