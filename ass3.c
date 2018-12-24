// ----------------------------------------------- -------------------------------
// ass3.c
//
// This is example of solitaire game with a little bit changed rules for exam. 
// Game is with 26 cards and 4 decks. Cards can have value between 1 and 14 
// and can be RED or BLACK
//
// Group: group 1, assistant Weinberger
//
// Authors: Weinberger, 0123456
// ----------------------------------------------- -------------------------------
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h> 

#define _GNU_SOURCE

struct _Card_{
	char colour_[10];
	int value_;
	struct _Card_ *next_;
	struct _Card_ *prev_;
};

struct _Card_ *head;
struct _Card_ *deck_1;
struct _Card_ *deck_2;
struct _Card_ *deck_3;
struct _Card_ *deck_4;
struct _Card_ *deck_5;
struct _Card_ *deck_6;
struct _Card_ **cd;

 // ------------------------------------------------ -----------------------------
///
/// This is the function which converts string representation of number to int value
/// readed with new line.
///
/// @param number_string String representation of number
///
/// @return int value of the card

int string_to_int(char *number_string){
	int number;
	if (strcmp(number_string, "A\n") == 0 || strcmp(number_string, "A") == 0)
		number = 1;
	if (strcmp(number_string, "2\n") == 0 || strcmp(number_string, "2") == 0)
		number = 2;
	if (strcmp(number_string, "3\n") == 0 || strcmp(number_string, "3") == 0)
		number = 3;
	if (strcmp(number_string, "4\n") == 0 || strcmp(number_string, "4") == 0)
		number = 4;
	if (strcmp(number_string, "5\n") == 0 || strcmp(number_string, "5") == 0)
		number = 5;
	if (strcmp(number_string, "6\n") == 0 || strcmp(number_string, "6") == 0)
		number = 6;
	if (strcmp(number_string, "7\n") == 0 || strcmp(number_string, "7") == 0)
		number = 7;
	if (strcmp(number_string, "8\n") == 0 || strcmp(number_string, "8") == 0)
		number = 8;
	if (strcmp(number_string, "9\n") == 0 || strcmp(number_string, "9") == 0)
		number = 9;
	if (strcmp(number_string, "10\n") == 0 || strcmp(number_string, "10") == 0)
		number = 10;
	if (strcmp(number_string, "J\n") == 0 || strcmp(number_string, "J") == 0)
		number = 12;
	if (strcmp(number_string, "Q\n") == 0 || strcmp(number_string, "Q") == 0)
		number = 13;
	if (strcmp(number_string, "K\n") == 0 || strcmp(number_string, "K") == 0)
		number = 14;
	return number;
 }
 
 // ------------------------------------------------ -----------------------------
///
/// This is the function which converts string representation of number to int value
/// readed without new line.
///
/// @param number_string String representation of number
///
/// @return int value of the card
 int string_to_int_without_new_line(char *number_string){
	int number;
	if (strcmp(number_string, "A") == 0)
		number = 1;
	if (strcmp(number_string, "2") == 0)
		number = 2;
	if (strcmp(number_string, "3") == 0)
		number = 3;
	if (strcmp(number_string, "4") == 0)
		number = 4;
	if (strcmp(number_string, "5") == 0)
		number = 5;
	if (strcmp(number_string, "6") == 0)
		number = 6;
	if (strcmp(number_string, "7") == 0)
		number = 7;
	if (strcmp(number_string, "8") == 0)
		number = 8;
	if (strcmp(number_string, "9") == 0)
		number = 9;
	if (strcmp(number_string, "10") == 0)
		number = 10;
	if (strcmp(number_string, "J") == 0)
		number = 12;
	if (strcmp(number_string, "Q") == 0)
		number = 13;
	if (strcmp(number_string, "K") == 0)
		number = 14;
	return number;
 }

// ------------------------------------------------ -----------------------------
///
/// This is the function which creates the new card.
///
/// @param y Colour of the new card
/// @param x Value of the new card
///
/// @return Card* New card with no prev and no next card.
struct _Card_ *get_new_card(char *y, int x) {
	struct _Card_ *new_card	= (struct _Card_ *)malloc(sizeof(struct _Card_));
	strncpy(new_card->colour_, y, 10);
	
	new_card->value_ = x;
	new_card->prev_ = NULL;
	new_card->next_ = NULL;

	return new_card;
}

// ------------------------------------------------ -----------------------------
///
/// This is the function which adds new card(node) to deck0(list) at head with values passed
/// by arguments.
///
/// @param y Colour of the new card
/// @param x Value of the new card
///
/// @return void 
void insert_at_head(char *y, int x) {
	struct _Card_ *new_card = get_new_card(y, x);
	if(head == NULL) {
		head = new_card;
		return;
	}
	head->prev_ = new_card;
	new_card->next_ = head; 
	head = new_card;
}

// ------------------------------------------------ -----------------------------
///
/// This is the function which adds new card(node) to deck[1-4](list) at head which is passed by argument.
///
/// @param l Deck where we want add new card from the deck0
///
/// @return void
void insert_at_head_list(struct _Card_ **l) {
	struct _Card_ *temp2 = head;
	head=head->next_;
	temp2->next_ = NULL;
	temp2->prev_ = NULL;
	(*l)=temp2;
	
}

// ------------------------------------------------ -----------------------------
///
/// This is the function which adds new card(node) to deck[1-4](list) at tail which is passed by argument.
///
/// @param l Deck where we want add new card from the deck0
///
/// @return void
void insert_at_tail_list(struct _Card_ **l) {
	struct _Card_ *temp = (*l);
	while(temp->next_ != NULL) 
		temp = temp->next_; 
	temp->next_ = head;
	head->prev_ = temp;
	head = head->next_;
	head->prev_ = NULL;
	temp = temp->next_;
	temp->next_ = NULL;
	
}

// ------------------------------------------------ -----------------------------
///
/// This is the function which adds new card(node) to deck0(list) at tail with values passed
/// by arguments.
///
/// @param y Colour of the new card
/// @param x Value of the new card
///
/// @return void 
void insert_at_tail(char *y,int x) {
	struct _Card_ *temp = head;
	struct _Card_ *new_card = get_new_card(y, x);
	if(head == NULL) {
		head = new_card;
		return;
	}
	while(temp->next_ != NULL) 
		temp = temp->next_;
	temp->next_ = new_card;
	new_card->prev_ = temp;
}

// ------------------------------------------------ -----------------------------
///
/// This function prints deck by straight order
///
/// @param deck_pointer pointer to deck which we want to print by straight order
///
/// @return void
void print(struct _Card_ **deck_pointer) {
	struct _Card_ *temp = (*deck_pointer);
	printf("\nForward: ");
	while(temp != NULL) {
		printf(" %s %d ",temp->colour_, temp->value_);
		temp = temp->next_;
	}
	printf("\n");
}

// ------------------------------------------------ -----------------------------
///
/// This function prints deck by reverse order
///
/// @param deck_pointer pointer to deck which we want to print by reverse order
///
/// @return void
void reverse_print(struct _Card_ **deck_pointer) {
	struct _Card_ *temp = (*deck_pointer);
	if(temp == NULL) 
		return; // empty list, exit

	while(temp->next_ != NULL) {
		temp = temp->next_;
	}
	while(temp != NULL) {
		printf(" %s %d ",temp->colour_, temp->value_);
		temp = temp->prev_;
	}
	printf("\n");
}

// ------------------------------------------------ -----------------------------
///
/// This function reads cards from configuration file.
///
/// @param file_path Location of configuration file.
/// @return bool is the configuration file valid or not
bool reading_conf_file(char *file_path){
	FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
	char *colour;
	char *number_string;
	int number;
	int brojac=0;

    fp = fopen(file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
		if(line[0] == '\n'){
		} 
		else {
		
			colour = strtok(line, " ");
			if(strcmp(colour, "RED") == 0 || strcmp(colour, "BLACK") == 0){		
		
		
				number_string = strtok(NULL, " ");
		
				number= string_to_int(number_string);
				brojac++;
				if(number < 1 || number >14 ){
					return false;
				}

				insert_at_head(colour, number);
			} 
			else{
				return false;
			}
		}
    }
	if(brojac < 26) 
		return false;
	
    fclose(fp);
	return true;
	
 }
 
 
  // ------------------------------------------------ -----------------------------
///
/// This is function which deal the cards. Taking cards from the deck0 and dealing
/// them by the game rule to other decks[1-4].
///
/// @noparam 
///
/// @return void
 void deal_cards(){
	insert_at_head_list(&deck_1);
	insert_at_head_list(&deck_2);
	insert_at_head_list(&deck_3);
	insert_at_head_list(&deck_4);
	
	insert_at_tail_list(&deck_2);
	insert_at_tail_list(&deck_3);
	insert_at_tail_list(&deck_4);
	
	insert_at_tail_list(&deck_3);
	insert_at_tail_list(&deck_4);
	
	insert_at_tail_list(&deck_4);
 }
  // ------------------------------------------------ -----------------------------
///
/// This function prints the selected card(node) from the deck(list)
///
/// @param deck Deck from which we want to print the selected card(node) from.
/// @param row Position of card in deck. 
///
/// @return void
 void print_selected_card(struct _Card_ *deck, int row){
	 if(deck!=NULL){
		 struct _Card_ *temp = deck;
		 char s[5] = {'\0'};
		
		 for(int i=0; i < row; i++) {
			 if((temp->next_) != NULL)
				temp = temp->next_; 
			 else{ 
				printf("     |");
				return;
			 }
		 }
		 if( strcmp(temp->colour_, "RED") == 0 ){
			 s[0]='R';
		 } else{
			 s[0]='B';
		 }
		 
		 switch(temp->value_){
			 case 1: 
				s[1]='A'; 
				s[2]=' ';
				s[3]=' ';
			
				break;
			 case 2: 
				s[1]='2';
				s[2]=' ';
				s[3]=' ';
					
				break;
			 case 3: 
				s[1]='3'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 4: 
				s[1]='4';
				s[2]=' ';
				s[3]=' ';	
								
				break;
			 case 5: 
				s[1]='5';
				s[2]=' ';
				s[3]=' ';
								
				break;
			 case 6: 
				s[1]='6'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 7: 
				s[1]='7';
				s[2]=' ';
				s[3]=' ';				
				
				break;
			 case 8: 
				s[1]='8'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 9: 
				s[1]='9';
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 10: 
				s[1]='1';
				s[2]='0'; 
				s[3]=' ';
				
				break;
			 case 12: 
				s[1]='J';
				s[2]=' ';
				s[3]=' ';
									
				break;
			 case 13: 
				s[1]='Q';
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 14: 
				s[1]='K';
				s[2]=' ';
				s[3]=' ';
				
				break;
			default :
				break;
			 
		 }
		s[4]='\0';
		printf(" %s|" , s);
		return;
	 }
	 else {
		 printf("     |");
		 return;
	 }
 }
   // ------------------------------------------------ -----------------------------
///
/// This function prints the selected card(node) from the deck(list)
///
/// @param deck Deck from which we want to print the selected card(node) from.
/// @param row Position of card in deck. 
///
/// @return void
 void print_selected_card_head(struct _Card_ *deck, int row){
	 if(deck!=NULL){
		 struct _Card_ *temp = deck;
		 char s[5] = {'\0'};
		
		 for(int i=0; i < row; i++) {
			 if((temp->next_) != NULL)
				temp = temp->next_; 
			 else{ 
				printf("     |");
				return;
			 }
		 }
		 if( strcmp(temp->colour_, "RED") == 0 ){
			 s[0]='R';
		 } else{
			 s[0]='B';
		 }
		 
		 switch(temp->value_){
			 case 1: 
				s[1]='A'; 
				s[2]=' ';
				s[3]=' ';
			
				break;
			 case 2: 
				s[1]='2';
				s[2]=' ';
				s[3]=' ';
					
				break;
			 case 3: 
				s[1]='3'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 4: 
				s[1]='4';
				s[2]=' ';
				s[3]=' ';	
								
				break;
			 case 5: 
				s[1]='5';
				s[2]=' ';
				s[3]=' ';
								
				break;
			 case 6: 
				s[1]='6'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 7: 
				s[1]='7';
				s[2]=' ';
				s[3]=' ';				
				
				break;
			 case 8: 
				s[1]='8'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 9: 
				s[1]='9';
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 10: 
				s[1]='1';
				s[2]='0'; 
				s[3]=' ';
				
				break;
			 case 12: 
				s[1]='J';
				s[2]=' ';
				s[3]=' ';
									
				break;
			 case 13: 
				s[1]='Q';
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 14: 
				s[1]='K';
				s[2]=' ';
				s[3]=' ';
				
				break;
			default :
				break;
			 
		 }
		s[4]='\0';
		printf("%s|" , s);
		return;
	 }
	 else {
		 printf("     |");
		 return;
	 }
 }
    // ------------------------------------------------ -----------------------------
///
/// This function prints the selected card(node) from the deck(list)
///
/// @param deck Deck from which we want to print the selected card(node) from.
/// @param row Position of card in deck. 
///
/// @return void
 void print_selected_card_last_deck(struct _Card_ *deck, int row){
	 if(deck!=NULL){
		 struct _Card_ *temp = deck;
		 char s[5] = {' '};
		
		 for(int i=0; i < row; i++) {
			 if((temp->next_) != NULL)
				temp = temp->next_; 
			 else{ 
				printf("     |");
				return;
			 }
		 }
		 if( strcmp(temp->colour_, "RED") == 0 ){
			 s[0]='R';
		 } else{
			 s[0]='B';
		 }
		 
		 switch(temp->value_){
			 case 1: 
				s[1]='A'; 
				s[2]=' ';
				s[3]=' ';
			
				break;
			 case 2: 
				s[1]='2';
				s[2]=' ';
				s[3]=' ';
					
				break;
			 case 3: 
				s[1]='3'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 4: 
				s[1]='4';
				s[2]=' ';
				s[3]=' ';	
								
				break;
			 case 5: 
				s[1]='5';
				s[2]=' ';
				s[3]=' ';
								
				break;
			 case 6: 
				s[1]='6'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 7: 
				s[1]='7';
				s[2]=' ';
				s[3]=' ';				
				
				break;
			 case 8: 
				s[1]='8'; 
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 9: 
				s[1]='9';
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 10: 
				s[1]='1';
				s[2]='0'; 
				s[3]=' ';
				
				break;
			 case 12: 
				s[1]='J';
				s[2]=' ';
				s[3]=' ';
									
				break;
			 case 13: 
				s[1]='Q';
				s[2]=' ';
				s[3]=' ';
				
				break;
			 case 14: 
				s[1]='K';
				s[2]=' ';
				s[3]=' ';
				
				break;
			default :
				break;
			 
		 }
		s[4]='\0';
		printf("%s" , s);
		return;
	 }
	 else {
		 printf("    ");
		 return;
	 }
 }
  // ------------------------------------------------ -----------------------------
///
/// This function prints the last card(node) from the deck(list)
///
/// @param deck Deck from which we want to print the last card(node).
///
/// @return void
 void print_last_card(struct _Card_ *deck){
	struct _Card_ *temp = deck;
	int i = 0;
	while(temp->next_ != NULL){ 
		temp = temp->next_;
		i++;
	}
	print_selected_card_head(deck, 0);
  }
  // ------------------------------------------------ -----------------------------
///
/// This function print the position of cards on decks and discard pile. The main 
/// screen through the game.
///
/// @noparam
///
/// @return void
 void print_cards(){
	 for(int i = 0; i < 7; i++){
		 if(i == 0) {
			printf("%d   |", i);
		 }
		  if(i > 0 && i < 5) {
			printf(" %d   |", i);
		 }
		 if(i == 5 ){
			 printf(" DEP |");
		 } 
		  if(i == 6 ){
			 printf(" DEP");
		 } 
	 }
	 printf("\n");
	 for(int i = 0; i < 39; i++){
		 printf("-");
	 }
	 printf("\n");
	 	for(int i = 0; i < 16; i++){
			for(int j = 0; j < 7; j++){
				if(i == 15 && j == 0){
					print_last_card(head);
				} else if(i < 15 && j == 0){	
						printf("X   |");
				  }
				  else if(i == 15 && j > 0 && j < 6){	
						printf("     |");
				  }
				  else if(i == 15 && j == 6){	
						printf("    ");
				  }
				 if(i < 15  && j == 1){	
						print_selected_card(deck_1, i);
				  }
				   if(i < 15  && j == 2){	
						print_selected_card(deck_2, i);
				  }
				   if(i < 15  && j == 3){	
						print_selected_card(deck_3, i);
				  }
				   if(i < 15  && j == 4){	
						print_selected_card(deck_4, i);
				  }
				   if(i < 15  && j == 5){	
						print_selected_card(deck_5, i);
				  }
				   if(i < 15  && j == 6){	
						print_selected_card_last_deck(deck_6, i);
				  }
			}
			printf("\n");
		}
	
 }
  // ------------------------------------------------ -----------------------------
///
/// This function read whole line from stdin
///
/// @noparam
///
/// @return char* array of char
 char *get_line(void) {
    char *line = malloc(100), *linep = line;
    size_t len_max = 100, len = len_max;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = len_max;
            char * linen = realloc(linep, len_max *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}
// ------------------------------------------------ -----------------------------
///
/// This function finds card which we want to move and deck where that card is also.
///
/// @param colour The colour of wanted card.
/// @param value The number of wanted card.
///
/// @return Card* pointer to card which we want to move
struct _Card_ *find_card_deck(char *colour, int value){
		struct _Card_ *temp;
		temp = head;
		while(temp->next_ != NULL) 
			temp = temp->next_;
		if(strcmp(temp->colour_, colour) == 0 && temp->value_ == value){
			cd = &head;
			return temp;
		}
		else{ 
			temp = NULL;
		}
		if (temp== NULL)
			temp = deck_1;
		while(temp!= NULL) {
			if(strcmp(temp->colour_, colour) == 0 && temp->value_ == value){
				cd = &deck_1;
				return temp;
			}
			else{
				temp = temp->next_;
			}		
		}
		if (temp == NULL)
			temp = deck_2;
		while(temp != NULL) {
			if(strcmp(temp->colour_, colour) == 0 && temp->value_ == value){
				cd = &deck_2;
				return temp;
			}
			else{
				temp = temp->next_;
			}		
		}
		if (temp== NULL)
			temp = deck_3;
		while(temp!= NULL) {
			if(strcmp(temp->colour_, colour) == 0 && temp->value_ == value){
				cd = &deck_3;
				return temp;
			}
			else{
				temp = temp->next_;
			}		
		}
		if (temp== NULL)
			temp = deck_4;
		while(temp!= NULL) {
			if(strcmp(temp->colour_, colour) == 0 && temp->value_ == value){
				cd = &deck_4;
				return temp;
			}
			else{
				temp = temp->next_;
			}		
		}
	return NULL;
}
// ------------------------------------------------ -----------------------------
///
/// This function checks cards in list after card which we want to move are in order
/// compared to card which we want to move.
///
/// @param current_node Card which we want to move
///
/// @return bool return if in cards are in order
bool is_in_order(struct _Card_ *current_node){
	struct _Card_ *temp = current_node;
	struct _Card_ *temp_2;
	if(temp->next_ != NULL)
		temp_2 = current_node->next_;
	else 
		return true;
	
	bool end = false;
	while(!end){
		
		if(strcmp(temp->colour_, temp_2->colour_) == 0 || ((temp->value_ - temp_2->value_) != 1))
			return  false;
		else 
			if(temp_2->next_ != NULL){
				temp = temp->next_;
				temp_2 = temp_2->next_;
			}
			else 
				return true;
	}
	return false;
}
// ------------------------------------------------ -----------------------------
///
/// This function checks if discard pile are in order. Actually cards on them with the
/// card which we want to move on discard pile.
///
/// @param current_node Card which we want to move
/// @param last_deck One of discard piles
///
/// @return bool return if in discard pile cards are in order 
bool is_in_order_last_two_deck(struct _Card_ *current_node, struct _Card_ *last_deck){
	struct _Card_ *temp_2 = last_deck;
	if(temp_2 == NULL ){
		if(current_node->next_ != NULL){
			return false;
		} else{
			if(current_node->value_ != 1 ){
				return false;
			}
			else{
				last_deck = current_node;
				return true;
			}
		}
		
	} else{
		while(temp_2->next_ != NULL) 
			temp_2 = temp_2->next_;
		if(strcmp(current_node->colour_, temp_2->colour_) != 0){
			return false;
		} else{
			if(current_node->value_ - temp_2->value_ == 1 && current_node->next_ == NULL){
				return true;
			} else{
				return false;
			}
		}
		
		
	}
	
}
// ------------------------------------------------ -----------------------------
///
/// This function swaps pointers to lists(decks).
///
/// @param current_deck pointer to pointer deck where card we want to move is
/// @param wanted_deck Pointer to pointer to list(deck), first card of list
///
/// @return void
void swap_deck(struct _Card_ **current_deck, struct _Card_ **wanted_deck){
	struct _Card_ *temp = (*wanted_deck);
	struct _Card_ *temp_2 = (*current_deck);
	
	struct _Card_ *tmp;
	
	tmp = temp;
	temp = temp_2;
	temp_2 = tmp;
	
	(*current_deck) = temp_2;
	(*wanted_deck) = temp;
}

// ------------------------------------------------ -----------------------------
///
/// This function moves card if it is by the rules of game. Moves one node to another
/// deck. 
///
/// @param current_deck pointer to deck where card we want to move is
/// @param wanted_deck Pointer to list(deck).
///
/// @return void
void move(struct _Card_ *current_deck, struct _Card_ **wanted_deck){
	struct _Card_ *temp;
	struct _Card_ *temp_2;
	
	temp = (*wanted_deck);
	temp_2 = current_deck;
	if(temp_2->prev_==NULL && temp != NULL ){
		while(temp->next_ != NULL) {
			temp = temp->next_;
		} 
		temp->next_ = temp_2;
		*cd = NULL;
		
	}
	if(temp_2->prev_ == NULL && temp == NULL  && temp_2 != head){
		swap_deck(cd, wanted_deck);
	}
	if(temp != NULL && temp_2->prev_ != NULL){
		while(temp->next_ != NULL) {
			temp = temp->next_;
		} 
		temp->next_ = temp_2;
		if(temp_2->prev_ != NULL){
			(temp_2->prev_)->next_ = NULL;
		}
		else{
		}
		temp_2->prev_ = temp;
	}  else if(temp_2->prev_ != NULL ){
		(temp_2->prev_)->next_ = NULL;
		(*wanted_deck) = temp_2;
		temp_2->prev_ = NULL;
	}
	else if(temp_2->prev_ != NULL ){
		(temp_2->prev_)->next_ = NULL;
		(*wanted_deck) = temp_2;
	}
	
		
}


// ------------------------------------------------ -----------------------------
///
/// This function count the number of nodes(cards) in one list(deck)
///
/// @param list List where all nodes will be counted
///
/// @return int age of spouse
int count(struct _Card_ *list)
{
    int nodes = 0;

    while (list != NULL) 
    {
        nodes++;
        list = list->next_;
    }

    return nodes;
}



// ------------------------------------------------ -----------------------------
///
/// This is function which swap 2 cards in list 
///
/// @param list Which deck(list) we want to shuffle
/// @param pos1 position of node which we want to swap
/// @param pos2 position of node where we want to swap 
///
/// @return int if nodes are swapped(1) or not(-1)
int swap(struct _Card_ *list, int pos_1, int pos_2)
{
    struct _Card_ *node_1, *node_2, *prev_1, *prev_2, *temp;
    int i;

    // Get the far position among both
    const int max_pos = (pos_1 > pos_2) ? pos_1 : pos_2;

    // Get total nodes in the list
    const int total_nodes = count(list);

    // Validate swap positions
    if ((pos_1 <= 0 || pos_1 > total_nodes) || (pos_2 <= 0 || pos_2 > total_nodes))
    {
        return -1;
    }
    
    // If both positions are same then no swapping required
    if (pos_1 == pos_2)
    {
        return 1;
    }


    // Identify both nodes to swap
    i = 1;
    temp  = list;
    prev_1 = NULL;
    prev_2 = NULL;

    // Find nodes to swap
    while (temp != NULL && (i <= max_pos))
    {
        if (i == pos_1 - 1)
            prev_1 = temp;
        if (i == pos_1)
            node_1 = temp;

        if (i == pos_2 - 1)
            prev_2 = temp;
        if (i == pos_2)
            node_2 = temp;

        temp = temp->next_;
        i++;
    }

    // If both nodes to swap are found.
    if (node_1 != NULL && node_2 != NULL)
    {
        // Link previous of node1 with node2
        if (prev_1 != NULL)
            prev_1->next_ = node_2;

        // Link previous of node2 with node1
        if (prev_2 != NULL)
            prev_2->next_ = node_1;

        // Swap node1 and node2 by swapping their 
        // next node links
        temp        = node_1->next_;
        node_1->next_ = node_2->next_;
        node_2->next_ = temp;

        // Make sure to swap head node when swapping
        // first element.
        if (prev_1 == NULL)
            head = node_2;
        else if (prev_2 == NULL)
            head = node_1;
    }

    return 1;
}
// ------------------------------------------------ -----------------------------
///
/// This function shuffle the nodes in deck before dealing the cards.
/// This function shuffle all 26 cards.
///
/// @noparam
///
/// @return void
void shuffle_deck(){

	
	int r = 0;
	int i = 0;
	for(int j = 0; j < rand() % 100; j++){
		r = rand() % 27;
		i = rand() % 27;
		swap(head, r, i);
	}
		
	
}
// ------------------------------------------------ -----------------------------
///
/// This function checks if the card can be moved to wanted deck.
///
/// @param current_node pointer to card which we want to move
/// @param want_deck pointer to deck(list) where we want to move card
///
/// @return bool if card be placed(true) or not(false)
bool can_place(struct _Card_ *current_node, struct _Card_ *want_deck){
	struct _Card_* temp = current_node;
	struct _Card_* temp_2 = want_deck;
		if(temp_2 != NULL){
			while(temp_2->next_ != NULL)
				temp_2 = temp_2->next_;
			
			if(temp_2->value_ != 12){
				if(((temp_2->value_ - temp->value_) == 1) && (strcmp(temp->colour_,temp_2->colour_) != 0))
					return true;
				else 
					return false;
			}
			else if(((temp_2->value_ - temp->value_) == 2) && (strcmp(temp->colour_,temp_2->colour_) != 0))
				return true;
			else 
				return false;
			}
		else 
			return true;
}
// ------------------------------------------------ -----------------------------
///
/// This function shifts all nodes in list forward by one place and last node before
/// shifting goes on first place.
///
/// @param tmp The list which will be shifted
///
/// @return void
void next_card_in_deck(struct _Card_ *tmp){
	int count_swap = count(head);
	
	for(int i = 2; i < count_swap; i++){
		swap(head, 1, i);
	}
	swap(head, 1, count_swap);
}
// ------------------------------------------------ -----------------------------
///
/// This function converts uppercase letters to lowcase letters.
///
/// @param str char* which will be converted all uppercase letters to lowcase 
/// letters
///
/// @return void
void to_lower(char* str){
	for(char *p = str; *p; ++p) 
		*p = (*p > 0x40 && *p < 0x5b ) ? *p | 0x60 : *p;
}
// ------------------------------------------------ -----------------------------
///
/// This function converts lowcase letters to uppercase letters.
///
/// @param str char* which will be converted all lowcase letters to uppercase 
/// letters
///
/// @return void
void to_upper(char* str){
	for(char *p = str; *p; ++p) 
		*p = (*p > 0x60 && *p < 0x7b) ? *p &(~0x20) : *p;
}
// ----------------------------------------------- -------------------------------
///
/// The main program.
/// Reads cards from configuration file and place them into decks. Reads user inputs and 
/// use them to play the soliatire. 
///
/// @param argc number of arguments in stdin
/// @param argv name of configuration file with extension 
///
/// @return always zero
//
int main(int argc, char *argv[]){
	
	head = NULL;  
	if(argc != 2){
		printf("[ERR] Usage: ./ass3 [file-name] \n");
		return 1;
	}
	if(reading_conf_file(argv[1])){
		char* user_input;
		

		
		
		deck_1 = NULL;
		deck_2 = NULL;
		deck_3 = NULL;
		deck_4 = NULL;
		deck_5 = NULL;
		deck_6 = NULL;
		struct _Card_* current_move = NULL;
		deal_cards();
		print_cards();
		printf("esp> ");

		
		while(strcmp(user_input = get_line(), "exit\n") != 0){
			char *command = strtok(user_input, " ");
			to_lower(command);
			//printf("%s", command);
			if(strcmp(command, "swap\n")  == 0){
				next_card_in_deck(head);
				print_cards();
				printf("esp> ");	
			} 
			if(strcmp(command, "help\n")  == 0){
				printf("possible command: \n- move <color> <value> to <stacknumber> \n- help \n- exit \n esp>");	
			}
			if(strcmp(command, "move")  == 0){
				bool cmd = false;
				char *colour = strtok(NULL, " ");
				to_upper(colour);
				if(strcmp(colour, "RED")!= 0 || strcmp(colour, "BLACK")!= 0)
					cmd = true;
				char *number = strtok(NULL, " ");
				to_upper(number);
				int value = string_to_int_without_new_line(number);	
				char *to = strtok(NULL, " ");
				to_upper(to);
				if(strcmp(to, "TO")!= 0)
					cmd = false;
				char *deck_number = strtok(NULL, " ");
				int deck_number_int = atoi(deck_number);
				if(deck_number_int <1 || deck_number_int>6)
					cmd = false;
				if(cmd){
					if((current_move = find_card_deck(colour, value)) != NULL){
						struct _Card_ **wanted_deck;
						switch(deck_number_int){
							case 1: 
								wanted_deck = &deck_1;
								break;
							case 2: 
								wanted_deck = &deck_2;
								break;
							case 3: 
								wanted_deck = &deck_3;
								break;
							case 4: 
								wanted_deck = &deck_4;
								break;
							case 5: 
								wanted_deck = &deck_5;
								break;
							case 6: 	
								wanted_deck = &deck_6;
								break;
							default :
								break;
						}
						if(deck_number_int < 5 && is_in_order(current_move) && can_place(current_move, *wanted_deck)){
							move(current_move, wanted_deck);
						} else if(deck_number_int > 4 && is_in_order_last_two_deck(current_move, *wanted_deck)){
							move(current_move, wanted_deck);
						}
						else 
							printf("[INFO] Invalid move command!\n");
						print_cards();
						printf("esp>");
					}
				}
				else
					printf("[INFO] Invalid command!\n esp >");
			}
		} 
	} else {
		printf("[ERR] Invalid file!\n");
		return 3;
	}
	
	return 0;
}
