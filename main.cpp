#include <iostream>
#include <stdlib.h>

using namespace std;

struct Dart{
    int heal = 1;
    int size = 1;
};
struct Striker{
    int heal = 2;
    int size = 2;
};
struct Wraith{
    int heal = 4;
    int size = 3;
};
struct Banshee{
    int heal = 6;
    int size = 4;
};
struct Spaceship{
    int x;
    int y;
};

void menu();
int show_menu();
void play_game(int &map_size, int &target_point);
void move_spaceship_left(Spaceship &my_spaceship);
void move_spaceship_right(Spaceship &my_spaceship);
void render_map(int &map_size, Spaceship &my_spaceship);

char cell_to_string(int value);

int main(){

    menu();
}

void menu(){
    int user_choice = show_menu();

    int map_size;
    int target_point;
    
    if (user_choice == 1){

        do{
            system("cls");
            cout << "enter the size of map = ";
            cin >> map_size;
        }while(map_size < 15);

        system("cls");
        cout << "enter the point = ";
        cin >> target_point;

        play_game(map_size, target_point);   
    }

    else if (user_choice == 2){

    }

    else if (user_choice == 3){
        exit(0);
    }
}

int show_menu(){
    cout << "Menu:" << endl;
    cout << " 1. start" << endl;
    cout << " 2. load" << endl;
    cout << " 3. exit" << endl;
    int user_choice;
    cin >> user_choice;

    return user_choice;
}

void play_game(int &map_size, int &target_point){

    Spaceship my_spaceship;

    my_spaceship.x = map_size - 1;
    my_spaceship.y = (map_size - 1) / 2;
    
    render_map(map_size, my_spaceship);
    
    char spaceship_direction;
    while (true){
        cin >> spaceship_direction;

        switch (spaceship_direction){
            case 'a':
                move_spaceship_left(my_spaceship); break;
            case 'd':
                move_spaceship_right(my_spaceship); break;
        }
        render_map(map_size, my_spaceship);
    }
    
}

void move_spaceship_left(Spaceship &my_spaceship){
    my_spaceship.y--;
}
void move_spaceship_right(Spaceship &my_spaceship){
    my_spaceship.y++;
}

void render_map(int &map_size, Spaceship &my_spaceship){
    int map[map_size][map_size] = {};
    
    map[my_spaceship.x][my_spaceship.y] = 1;

    for (int ifor = 0; ifor < map_size * 2; ifor++){
        if (ifor % 2 == 0){
            for (int j = 0; j < map_size; ++j) {
                cout << " ---";
            }
            cout << endl;
            continue;
        }

        int i = ifor / 2;
        for (int j = 0; j < map_size; j++){
            cout << "| " << cell_to_string(map[i][j]) << " ";
        }

        cout << "|" << endl;
    }

    for (int j = 0; j < map_size; j++){
        cout << " ---";
    }
    cout << endl;
}

char cell_to_string(int value){
    char cell;
    switch (value){
        case 0:
            cell = ' ';
            break;
        case 1:
            cell = '#';
            break;
        case 2:
            cell = '^';
            break;
        case 3:
            cell = '*';
            break;
    }

    return cell;
}