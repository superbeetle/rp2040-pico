# Display Image & text on I2C driven ssd1306 OLED display 
from machine import Pin, I2C
from ssd1306 import SSD1306_I2C
import framebuf
import ufont

class OLED13306:
    def __init__(self,scl=Pin(13), sda=Pin(12), freq=200000,width=128,height=32):
        self.width=width                                           		 # oled display width
        self.height=height                                             # oled display height
        self.i2c = I2C(0, scl=scl, sda=sda, freq=freq)       				 # Init I2C using pins GP8 & GP9 (default I2C0 pins)
        print("I2C Address      : "+hex(self.i2c.scan()[0]).upper())          # Display device address
        print("I2C Configuration: "+str(self.i2c))                   		 # Display I2C config
        self.oled = SSD1306_I2C(width, height, self.i2c)                  		 # Init oled display
        self.f = ufont.BMFont("unifont-14-12888-16.v3.bmf")  # 中文显示对象
        # Raspberry Pi logo as 32x32 bytearray
        buffer = bytearray(b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00|?\x00\x01\x86@\x80\x01\x01\x80\x80\x01\x11\x88\x80\x01\x05\xa0\x80\x00\x83\xc1\x00\x00C\xe3\x00\x00~\xfc\x00\x00L'\x00\x00\x9c\x11\x00\x00\xbf\xfd\x00\x00\xe1\x87\x00\x01\xc1\x83\x80\x02A\x82@\x02A\x82@\x02\xc1\xc2@\x02\xf6>\xc0\x01\xfc=\x80\x01\x18\x18\x80\x01\x88\x10\x80\x00\x8c!\x00\x00\x87\xf1\x00\x00\x7f\xf6\x00\x008\x1c\x00\x00\x0c \x00\x00\x03\xc0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")
        # Load the raspberry pi logo into the framebuffer (the image is 32x32)
        fb = framebuf.FrameBuffer(buffer, 32, 32, framebuf.MONO_HLSB)
        # Clear the oled display in case it has junk on it.
        self.oled.fill(0)
        # Blit the image from the framebuffer to the oled display
        self.oled.blit(fb, 96, 0)
        # Add some text
        self.oled.text("Raspberry Pi",5,5)
        self.oled.text("Pico",5,15)
        # Finally update the oled display so the image & text is displayed
        self.oled.show()
    
    # 清空屏幕
    def clear(self):
        self.oled.fill(0)
        self.oled.show()
        
    # 闪屏
    def blink(self):
        self.oled.fill(1)
        self.oled.show()
        self.oled.fill(0)
        self.oled.show()
    
    def show(self):
        self.oled.show()
        
    # 填写文本
    def text(self,text="",x=5,y=5,color=1,reverse=False,clear=True,show=True,font_size=16):
#         self.oled.text(text,x,y,font_size)
        if clear :
            self.oled.fill(0)
        if font_size < 16:
            self.oled.text(text,x,y,font_size)
            if show :
                self.oled.show()
        else:
            self.f.text(
                display=self.oled,  # 显示对象 必要
                string=text,  # 显示的文字 必要
                x=x,  # x 轴
                y=y,  # y 轴
                color=color,  # 颜色 默认是 1(黑白)
                font_size=font_size, # 字号(像素)
                reverse=reverse, # 逆置(墨水屏会用到)
                clear=False,  # 显示前清屏
                show=show  # 是否立即显示
            )

if __name__ == "__main__":
    from machine import Pin
    import utime
    from I2C13306 import OLED13306
    # 显示启动
    oled=OLED13306(scl=Pin(13), sda=Pin(12))
    utime.sleep(3)
    oled.text("一二三四",font_size=18)
    utime.sleep(3)
    oled.text("一二三四五六七八",x=0,y=0,font_size=16)
    utime.sleep(3)
    oled.text("Next ...",font_size=18)



