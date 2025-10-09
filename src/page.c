#include "page.h"

static PageStateMachine active_page_selector = {0};

Page *get_active_page_loc() {
  return active_page_selector.active_page;
}

Page *get_next_page() {
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
    active_page_selector.active_index++;
    int index = active_page_selector.active_index; //just for readability
    active_page_selector.active_page = active_page_selector.pages[index];
    
    Page *page_loc = active_page_selector.pages[index];
    active_page_selector.active_page = page_loc;
    printf("returning next page!, page loc: %x", (int) page_loc);
    return page_loc;
  }
  
  // Case where we are at the last active page. 
  else {
    active_page_selector.active_index = 0;
    active_page_selector.active_page = active_page_selector.pages[0]; 
    Page *page_loc = get_active_page_loc();
    printf("returning first page!, page loc: %x\n", (int) page_loc);
    return page_loc;
  }
}

int init_page_state_machine() {
  active_page_selector.active_index = MAX_NUMBER_OF_PAGES + 1; //makes sure that the 0th loc is the next one returned when get_next_page is called.
}

int add_page(Page *page_loc) {
  printf("current active pages: %x\n, page to add: %x\n", (int) active_page_selector.number_of_pages, page_loc);
  Page *page_array_loc = &active_page_selector.pages;
  Page *new_page_loc = page_array_loc + active_page_selector.number_of_pages; //gets the postiion of the last page.
  printf("page array start: %x, writing to: %x\n", (int) page_array_loc, new_page_loc);
  active_page_selector.pages[active_page_selector.number_of_pages] = page_loc; 

  active_page_selector.number_of_pages++;
  return 0;
}
