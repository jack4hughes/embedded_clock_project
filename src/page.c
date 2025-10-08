#include "page.h"

static PageStateMachine active_page_selector = {0};

Page *get_active_page_loc() {
  return active_page_selector.active_page;
}

Page *get_next_page() {
  if (active_page_selector.number_of_pages == 0) {
    return NULL; //error when no pages are set.
  }
  
  active_page_selector.active_index++;
  
  //case where we are not at the last active page.
  if (
    active_page_selector.active_index < active_page_selector.number_of_pages
  ) {
    Page *page_loc = get_active_page_loc();
    return page_loc;
  }
  
  // Case where we are at the last active page. 
  else {
    active_page_selector.active_index = 0;
    Page *page_loc = get_active_page_loc();
    return page_loc;
  }
}

int init_page_state_machine() {
  active_page_selector.active_index = MAX_NUMBER_OF_PAGES + 1; //makes sure that the 0th loc is the next one returned when get_next_page is called.
}

int add_page(Page *page_loc) {
  active_page_selector.number_of_pages++;
  active_page_selector.pages[active_page_selector.number_of_pages - 1] = page_loc; //this horrible line of code writes the page loc to our page list.
  return 0;
}
