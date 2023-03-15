#include <Arduino.h>

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include "Adafruit_SPIDevice.h"
#include <Adafruit_FT6206.h>

#include "../lvgl/src/lvgl.h"

  //#define TFT_DC     25
  //#define TFT_CS      5

#define _cs   5  // goes to TFT CS
#define _dc   25  // goes to TFT DC
#define _mosi 23  // goes to TFT MOSI
#define _sclk 18  // goes to TFT SCK/CLK

// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341((int8_t)_cs, (int8_t)_dc, _mosi, _sclk);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one I am using, it is 340 ohms across the X plate
Adafruit_FT6206 ts = Adafruit_FT6206();
TS_Point oldPoint;

static lv_disp_buf_t disp_buf; //LVGL stuff;
static lv_color_t buf[LV_HOR_RES_MAX * 10];
lv_disp_drv_t disp_drv;
lv_indev_drv_t indev_drv;

lv_obj_t * btn1;
lv_obj_t * btn2;
lv_obj_t *screenMain;
lv_obj_t *label;

static void event_handler_btn(lv_obj_t * obj, lv_event_t event){
    Serial.println("event_handler_btn");
    if(event == LV_EVENT_CLICKED) {
        if (obj == btn1)
        lv_label_set_text(label, "Hello");
        else if (obj == btn2){
          lv_label_set_text(label, "Goodbye");
        }
    }
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    uint32_t wh = w*h;

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    while (wh--) tft.pushColor(color_p++->full);//for Adafruit library
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

bool my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{

    Serial.println("Click detected");
    TS_Point p = ts.getPoint();
  
    data->state = LV_INDEV_STATE_PR;
    data->point.x = p.x*240/1024; //we need to do some math to get x value between 0 and 239 (the width of the display).
    data->point.y = p.y*320/1024; //we need to do some math to get x value between 0 and 319 (the height of the display).
    oldPoint.x = p.x;
    oldPoint.y = p.y;

  return false; /*No buffering now so no more data read*/
}


void setup2(){

  analogReadResolution(10);

  oldPoint = ts.getPoint();

  lv_init();

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 240;
  disp_drv.ver_res = 320;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  
  lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_input_read;         /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/


  screenMain = lv_obj_create(NULL, NULL);

  label = lv_label_create(screenMain, NULL);
  lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
  lv_label_set_text(label, "Press a button");
  lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
  lv_obj_set_size(label, 240, 40);
  lv_obj_set_pos(label, 0, 15);

  btn1 = lv_btn_create(screenMain, NULL);
  lv_obj_set_event_cb(btn1, event_handler_btn);
  lv_obj_set_width(btn1, 70);
  lv_obj_set_height(btn1, 32);
  lv_obj_set_pos(btn1, 32, 130);

  lv_obj_t * label1 = lv_label_create(btn1, NULL);
  lv_label_set_text(label1, "Hello");

  btn2 = lv_btn_create(screenMain, NULL);
  lv_obj_set_event_cb(btn2, event_handler_btn);
  lv_obj_set_width(btn2, 70);
  lv_obj_set_height(btn2, 32);
  lv_obj_set_pos(btn2, 142, 130);

  

  lv_obj_t * label2 = lv_label_create(btn2, NULL);
  lv_label_set_text(label2, "Goodbye");

  static lv_style_t style1;
  lv_style_init(&style1);
  lv_style_set_text_color(&style1, LV_STATE_DEFAULT, LV_COLOR_GREEN);
  lv_style_set_border_color(&style1, LV_STATE_DEFAULT, LV_COLOR_RED);
  lv_style_set_border_width(&style1, LV_STATE_DEFAULT, 2);
  lv_style_set_bg_color(&style1, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
  lv_style_set_bg_opa(&style1, LV_STATE_DEFAULT, 255);
  lv_style_set_radius(&style1, LV_STATE_DEFAULT, 1);
  

  static lv_style_t style2;
  lv_style_init(&style2);
  lv_style_set_text_color(&style2, LV_STATE_DEFAULT, LV_COLOR_GRAY);
  lv_style_set_border_color(&style2, LV_STATE_DEFAULT, lv_color_hex(0x222222));
  lv_style_set_border_width(&style2, LV_STATE_DEFAULT, 1);
  lv_style_set_bg_color(&style2, LV_STATE_DEFAULT, lv_color_hex(0x222222));
  lv_style_set_bg_opa(&style2, LV_STATE_DEFAULT, 255);
  lv_style_set_radius(&style2, LV_STATE_DEFAULT, 4);
  lv_style_set_shadow_spread(&style2, LV_STATE_DEFAULT, 1);
  lv_style_set_shadow_color(&style2, LV_STATE_DEFAULT, LV_COLOR_GRAY);
  lv_style_set_shadow_opa(&style2, LV_STATE_DEFAULT, 255);
  lv_style_set_shadow_width(&style2, LV_STATE_DEFAULT, 1);

  static lv_style_t bigStyle;
  lv_style_init(&bigStyle);
  lv_style_set_text_font(&bigStyle ,LV_STATE_DEFAULT, &lv_font_montserrat_36);



  lv_obj_add_style(label, LV_LABEL_PART_MAIN, &bigStyle);

  //lv_obj_add_style(btn1, LV_LABEL_PART_MAIN, &style1);

  //lv_obj_add_style(btn2, LV_LABEL_PART_MAIN, &style2);
  

  lv_scr_load(screenMain);
}


void setup() {
  Serial.begin(9600);

  while (!Serial)
  {
    sleep(300);
  }
  
  Serial.println("Starting setup");

  tft.begin();
  tft.setRotation(0);
  
  setup2();
  
  /*
  tft.setCursor(0, 30);
  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  tft.print("Aircon status: ");
  
  tft.setCursor(0, 60);
  tft.print("Aircon temp: ");
  tft.print((char)247); // degree symbol
  tft.println("C");
  */

}

void loop() {

  lv_task_handler();

  delay(1);
}