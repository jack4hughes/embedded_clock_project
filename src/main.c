#include "bitmap.h"
#include "bitmap_displayer_mac.h"
#include "time_getter_mac.h"

int main(void) {

    
    int bitmap[BITMAP_ROWS][BITMAP_COLS] = {0};
    const Character zero = create_character(0, 5, 5, (const int*)ZERO_5X5);
    const Character one = create_character(1, 5, 5, (const int*)ONE_5X5);
    const Character two = create_character(1, 5, 5, (const int*)TWO_5X5);
    const Character three = create_character(1, 5, 5, (const int*)THREE_5X5);
    const Character four = create_character(1, 5, 5, (const int*)FOUR_5X5);
    const Character five = create_character(1, 5, 5, (const int*)FIVE_5X5);
    const Character six = create_character(1, 5, 5, (const int*)SIX_5X5);
    const Character seven = create_character(1, 5, 5, (const int*)SEVEN_5X5);
    const Character eight = create_character(1, 5, 5, (const int*)EIGHT_5X5);
    const Character nine = create_character(1, 5, 5, (const int*)NINE_5X5);
    const Character colon = create_character(1, 5, 5, (const int*)COLON_5X5);
// Map
    /* int bool_at_3_3 = get_character_bool_from_position(one, 4, 4);
    int bool_at_3_4 = get_character_bool_from_position(one, 3, 4);
    int bool_at_4_3 = get_character_bool_from_position(one, 4, 3);
  
    add_character_to_bitmap(bitmap, one, 0, 0);
    add_character_to_bitmap(bitmap, two, 5, 0);
    add_character_to_bitmap(bitmap, colon, 10, 0);
    add_character_to_bitmap(bitmap, one, 15, 0);
    add_character_to_bitmap(bitmap, five, 20, 0); 
    print_bitmap((int *)bitmap);    
   */
    printf("All characters initialised!\n");
    char time_string[6];
    get_time_string(time_string);
    printf("time string: %s\n", time_string);
    update_bitmap_with_string(bitmap, time_string);
    print_bitmap(bitmap);
    return 0;  // Added return value
}
