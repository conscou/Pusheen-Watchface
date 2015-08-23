#include <pebble.h>
  
static Window *main_window;  //creating the pointer to the main window, to be access when init() and deinit() are called 
static TextLayer *time_layer; //creating the pointer to the text layer of main window 
static BitmapLayer *pusheen_layer;  //creating pusheen
static GBitmap *pusheen_bitmap;    //creating pusheen

static void main_window_load(Window *window) { }

static void main_window_unload(Window *window) {  //destorys layers before destorying actual window
  gbitmap_destroy(pusheen_bitmap);
  bitmap_layer_destroy(pusheen_layer);
  text_layer_destroy(time_layer);
}

/*****FROM TUTORIAL******/
static void update_time() {
  
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  static char buffer[] = "00:00";
  
  if(clock_is_24h_style() == true) {
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else { 
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // display time on the TextLayer
  text_layer_set_text(time_layer, buffer);
}
/***********************/


static void updatePusheen(struct tm *current_time){
 if(clock_is_24h_style() == true) {
    
   if((current_time->tm_hour >=0 && current_time->tm_hour<=6) || (current_time->tm_hour >=20 && current_time->tm_hour<=23)){
        
        time_layer = text_layer_create(GRect(0, 100, 144, 50));
        text_layer_set_background_color(time_layer, GColorBlack);
        text_layer_set_text_color(time_layer, GColorWhite);
       
        text_layer_set_text(time_layer, "00:00");
        text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
        text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
        layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(time_layer));
        pusheen_bitmap = gbitmap_create_with_resource(RESOURCE_ID_PUSHEEN_WHITE);
        pusheen_layer = bitmap_layer_create(GRect(0, 25, 144, 70));
        bitmap_layer_set_background_color(pusheen_layer, GColorBlack);
        bitmap_layer_set_bitmap(pusheen_layer, pusheen_bitmap);
        layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(pusheen_layer));

        window_set_background_color(main_window, GColorBlack); 
    
     

    } else {
        time_layer = text_layer_create(GRect(0, 100, 144, 50));
        text_layer_set_background_color(time_layer, GColorWhite);
        text_layer_set_text_color(time_layer, GColorBlack);
       
        text_layer_set_text(time_layer, "00:00");
        text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
        text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
        layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(time_layer));
        pusheen_bitmap = gbitmap_create_with_resource(RESOURCE_ID_PUSHEEN_BLACK);
        pusheen_layer = bitmap_layer_create(GRect(0, 25, 144, 70));
        bitmap_layer_set_background_color(pusheen_layer, GColorWhite);
        bitmap_layer_set_bitmap(pusheen_layer, pusheen_bitmap);
        layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(pusheen_layer));

        window_set_background_color(main_window, GColorWhite); 
  
   }
  
  }

}
  
static void init() {
  


  main_window = window_create();  //creating the actual window and having it assigned to the main_window pointer
  
  time_t updateTime = time(NULL); 
  struct tm *pusheen_time = localtime(&updateTime);
  
  updatePusheen(pusheen_time);
  
  
   /* text_layer_set_background_color(time_layer, GColorBlack);
    text_layer_set_text_color(time_layer, GColorWhite);
    text_layer_set_text(time_layer, "00:00");

  // improve the layout to be more like a watchface
    text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
    text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);

  // add it as a child layer to the Window's root layer
    layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(time_layer));
    
  //set up pusheen picture
    pusheen_bitmap = gbitmap_create_with_resource(RESOURCE_ID_PUSHEEN_WHITE);
  //position image
    pusheen_layer = bitmap_layer_create(GRect(0, 25, 144, 70));
  //put bitmap and layer together
    bitmap_layer_set_bitmap(pusheen_layer, pusheen_bitmap);
  //add it to the parent
    layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(pusheen_layer));

  
  window_set_background_color(main_window, GColorBlack);  //change background color of window*/

  
  window_set_window_handlers(main_window, (WindowHandlers) {
  .load = main_window_load,
  .unload = main_window_unload
    });
  //push it all to the window
   window_stack_push(main_window, true);

   update_time();
}

static void deinit() {
    window_destroy(main_window);  //always destory main window
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

