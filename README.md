# edidvic
CTA-861-G and VESA DMT Monitor Timing Reference 


### CTA-861-G
```
$ ./edidvic.exe vic 97
  Pixel Clock: 594.0 MHz (*2 = 1188.0 MHz)
   Frame Rate: 60.000000 Hz (*2 = 120.000000 Hz)
     H Active: 3840
H Front Porch: 176
       H Sync: 88
 H Back Porch: 296
      H Total: 4400
     V Active: 2160
V Front Porch: 8
       V Sync: 10
 V Back Porch: 72
      V Total: 2250
        Flags: +hsync +vsync
Active Pixels: 8294400
 Total Pixels: 9900000
   8b10b Rate: 5940.0 MHz (/25 = 237.600 MHz)
```

### VESA DMT
```
$ ./edidvic.exe dmt 4
  Pixel Clock: 25.175 MHz (*2 = 50.350 MHz)
   Frame Rate: 59.940475 Hz (*2 = 119.880951 Hz)
     H Active: 640
H Front Porch: 16
       H Sync: 96
 H Back Porch: 48
      H Total: 800
     V Active: 480
V Front Porch: 10
       V Sync: 2
 V Back Porch: 33
      V Total: 525
        Flags: -hsync -vsync
Active Pixels: 307200
 Total Pixels: 420000
   8b10b Rate: 251.750 MHz (/25 = 10.70 MHz)

```