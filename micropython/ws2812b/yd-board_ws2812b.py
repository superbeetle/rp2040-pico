import ws2812b
import utime

'''
YD板载RGB灯默认GPIO脚是23，找到板上rsb字样脚，未焊接的（默认不焊接，估计是想由用户外部串多几个灯），需要焊接上
ws2812b(num, sm, pin)
num代表ws2812的数量
sm是内核，目前需要设置为0
pin是使用的引脚
set_pixel(n, r, g, b)
n是第几个ws2812
r, b, b是红绿蓝颜色
show()，刷新显示
fill((r, g, b))，填充所有ws2812
set_pixel_line(n1,n2,r,g,b)，设置从n1到n2颜色
set_pixel_line_gradient(n1,n2,r1,g1,b1,r2,g2,b2)，设置从n1到n2渐变色
'''

pixels = ws2812b.ws2812b(1,0,23)
#设置10个RGB灯 状态0 GPIO0
# pixels.set_pixel(0,255,0,0)
# pixels.set_pixel_line(0,7,0,10,0)
# pixels.set_pixel_line(1,1,0,10,0)
# pixels.fill(i,0,0)
# pixels.show()

# 红\绿\蓝渐变
i=0
# 渐变方向
direct='up'
led='red'

while True:
    if direct=='up':
        i=i+5
    if direct=='down':
        i=i-5
    if led == 'red':
        pixels.fill(i,0,0)
    if led == 'green':
        pixels.fill(0,i,0)
    if led == 'blue':
        pixels.fill(0,0,i)
        
    pixels.show()
#     utime.sleep_ms(20)
    print(i,direct)
    
    # 改变方向
    if i==255:
        direct='down'
    if i==0:
        direct='up'
        if led=='red':
            led='green'
        elif led=='green':
            led='blue'
        else:
            led='red'
        
    
    
    