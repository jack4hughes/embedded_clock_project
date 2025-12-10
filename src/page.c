#include "page.h"

static ClockModeStateMachine active_page_selector = {0};

ClockMode *get_active_page_loc() {
  return active_page_selector.active_page;
}

ClockMode *get_next_page() {
    //TODO: Check This for rewrites.
  if (active_page_selector.number_of_pages == 0) {
    printf("No pages have been created yet! \n");
    return NULL; //error when no pages are set.
  }
  
  active_page_selector.active_index++;
  
  //case where we are not at the last active page.
  if (
    active_page_selector.active_index < active_page_selector.number_of_pages
  ) {
    int index = active_page_selector.active_index; //just for readability
    printf("Current page index: %d", index);
    active_page_selector.active_page = active_page_selector.pages[index];
    
    ClockMode *page_loc = active_page_selector.pages[index];
    active_page_selector.active_page = page_loc;
    printf("returning next page!, page loc in page array: %p\n", (void *) page_loc);
    if (page_loc != 0) {
      return page_loc;
    }
    else {
      printf("PAGE STATE MACHINE ERROR: ClockMode not initialised! \n");
      printf("returning to first page.");
      active_page_selector.active_index = 0;
      active_page_selector.active_page = active_page_selector.pages[0]; 
      ClockMode *page_loc = get_active_page_loc(); //hello?
      printf("returning first page!, page loc: %p\n", (void *) page_loc);
      return page_loc;
    }
  }
  
  // Case where we are at the last active page. 
  else {
    active_page_selector.active_index = 0;
    active_page_selector.active_page = active_page_selector.pages[0];
    ClockMode *page_loc = get_active_page_loc();
    printf("returning first page!, page loc: %p\n", (void *) page_loc);
    return page_loc;
  }
}

int init_page_state_machine() {
  active_page_selector.active_index = 0xFF; //makes sure that the 0th loc is the next one returned when get_next_page is called.
  return 0; //indicate that page state machine has been set up cprrectly.  
}

int add_page(ClockMode *page_loc) {
  printf(
    "current active pages: %x, page to add: %p\n", 
    active_page_selector.number_of_pages,  
    (void *) page_loc
  );

  ClockMode *page_array_loc = &active_page_selector.pages;
  ClockMode *new_page_loc = page_array_loc + active_page_selector.number_of_pages; //gets the postiion of the last page.
  
  active_page_selector.pages[active_page_selector.number_of_pages] = page_loc;
  
  if (active_page_selector.pages[active_page_selector.number_of_pages] == NULL) {
    printf("ERROR: Page not intialised properly! Null pointer exception.\n");
    printf("\tInitial pointer location:  %p\n\tArray pointer location:    %p\n\tnew_page_pointer_location: %p\n",
           (void *) page_array_loc,
           (void *) new_page_loc,
           (void *) &active_page_selector.pages[active_page_selector.number_of_pages]
           );
    return -1; //Throw an error if the next page hasnt been added correctly.
  }

  active_page_selector.number_of_pages++; //if this hasnt failed, 
  return 0;
}
