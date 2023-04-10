#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX INT_MAX //MAX number of integers

typedef struct event
{
  char day[10];
  int hour;
  int minute;
  char description[41];

} Event; // declaring functions of struct event to Event

//Function decleration
int InputRange(int min, int max);
Event *InputEvent(Event *newEvent);
int AddEventAtIndex(Event list[], Event e, int i);
int InsertionSortEvent(Event list[], int *p_size, Event e);
void DisplayEvent(Event e);
void DisplayEventList(Event list[], int size);
int DeleteEvent(Event list[], int i, int *p_size);

// This function is too make sure the user inputs a number in between a particular range. It returns the range to other functions
int InputRange(int min, int max)
{
  int store;
  do
  {
    printf("Enter a number between %d and %d: ", min, max);
    scanf("%d", &store);
    printf("\n");

    if (store < min || store > max)
      printf("invalid Input\n");

  } while (store < min || store > max);

  return store; // returns the digit to the function which it was called
}

//This function has a pointer parameter. It calls event time in hours and minutes
Event *InputEvent(Event *newEvent)
{
  if (newEvent != NULL) // if condition to make sure pointer isnt null
  {

    printf("What day is this event: \n");

    scanf(" %[^\n]s", newEvent->day); //gets the day of the event and stores in the pointer to the day variable in the event struct

    printf("Enter the event time: \n");

    newEvent->hour = InputRange(0, 23); // newEvent calling hour in the struct

    newEvent->minute = InputRange(0, 59); // newEvent calling minute in the struct

    printf("Enter the event description: ");

    scanf(" %[^\n]s", newEvent->description); // gets the event description and stores it in  newEvent->description
  }
  else
  {
    return newEvent;
  }
  return newEvent;
}

// This function is used to store the events from the events list. It takes the EventList as a paramater, an event thats already populted and a valid index i, then overwrites the event i
int AddEventAtIndex(Event list[], Event e, int i)
{
  list[i] = e;
  return i;
}

//This function takes the parameters of EventList array, evenListSize by reference and the event e to make sure the values entered are valid
int InsertionSortEvent(Event list[], int *p_size, Event e)
{

  int index = *p_size;

  if (*p_size == 0)
  {
    list[0] = e;
    ++(*p_size);
    return 0;
  }
  else if (*p_size > 0)
  {
    for (int x = 0; x < *p_size; x++)
    {
      if (((list[x]).hour > e.hour) || (((list[x]).hour == e.hour) && ((list[x]).minute > e.minute)))
      {
        index = x;
        break;
      }
    }

    for (int x = *p_size; x >= index + 1; x--)
    {
      list[x] = list[x - 1];
    }

    AddEventAtIndex(list, e, index);
    ++(*p_size);

    return index;
  }
  else
  {
    return *p_size;
  }
}

//Displays the event
void DisplayEvent(Event e)
{
  printf("On %s at %02d:%02d hrs, you have an Event titled: %s\n", e.day, e.hour, e.minute, e.description);
}

void DisplayEventList(Event list[], int size)
{
  for (int x = 0; x < size; x++)
  {
    printf("\n[%d] ", x);
    DisplayEvent(list[x]);
  }
}

int DeleteEvent(Event list[], int i, int *p_size)
{
  for (int x = i; x < *p_size - 1; x++)
  {
    list[i] = list[i + 1];
  }
  --(*p_size);
  return 1;
}

void PrintMenu(void)
{ //The menu for EventScheduler
  puts("\n__= Scheduler v1.0 =__");
  puts("   1. Schedule an event.");
  puts("   2. Delete an event.");
  puts("   3. Display schedule.");
  puts("   4. Exit");
  printf("==> ");
}

int main()
{
  Event EventList[MAX];
  Event tempEvent;
  int eventListSize = 0;
  int opt = 1;
  int id;
  PrintMenu();
  opt = InputRange(1, 4);

  while (opt != 5)
  {
    switch (opt)
    {
    case 1:
      if (eventListSize < MAX)
      {
        InsertionSortEvent(EventList, &eventListSize, *InputEvent(&tempEvent));
      }
      else
      {
        printf("You've reached the maximum number of events you can add to the schedule!\n");
      }
      break;

    case 2:
      if (eventListSize == 0)
      {
        printf("You need to have an event to delete one \n");
      }
      else
      {
        printf("Which event would you like to delete (-1 to cancel)? \n");
        ;
        scanf("%d", &id);
        if (id == -1)
        {
          printf("Canceling...\n");
        }
        else if (DeleteEvent(EventList, id, &eventListSize) == -1)
        {
          printf("Deleting the event has failed \n");
          printf("Possible reasons event could not delete: \n 1: I is not in a valid range of events in the array \n 2: The list is already empty");
        }
        else
        {
          printf("Event deleted successfully!\n");
        }
      }

      break;

    case 3:
      if (eventListSize == 0)
      {
        printf("You need to have an event to display first \n");
      }
      else
      {
        printf("____=Schedule=____\n");
        DisplayEventList(EventList, eventListSize);
      }

      break;

    case 4:
      exit(0);
    }
    PrintMenu();
    opt = InputRange(1, 4);
  }

  return 0;
}
