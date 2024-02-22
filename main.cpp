#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Enemy{
    string name;
    int x;
    int y;
    int heal;
    int size;
    int point;
};
struct Spaceship{
    int x;
    int y;
};
struct Bullet{
    int x;
    int y;
};
struct Game{
    int map_size;
    int target_point;
    Spaceship spaceship;
    Enemy enemy;
    vector<Bullet> bullets;
};

void start_game();
int show_menu();
void play_game(int &map_size, int &target_point);
void move_bullets(vector<Bullet> &bullets);
void move_spaceship_left(Spaceship &my_spaceship, vector<Bullet> &bullets, Enemy &enemy);
void move_spaceship_right(Spaceship &my_spaceship, int &map_size, vector<Bullet> &bullets, Enemy &enemy);
Enemy create_enemy(int &map_size);
void render_map(int &map_size, Spaceship &my_spaceship, vector<Bullet> &bullets, Enemy &enemy);
char cell_to_string(int value);

int main(){

    start_game();
}

void start_game(){
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
    vector<Bullet> bullets;

    my_spaceship.x = map_size - 1;
    my_spaceship.y = (map_size - 1) / 2;

    Enemy first_enemy = create_enemy(map_size);

    render_map(map_size, my_spaceship, bullets, first_enemy);
    
    char spaceship_direction;
    while (true){
        cin >> spaceship_direction;

        switch (spaceship_direction){
            case 'a':
                move_spaceship_left(my_spaceship, bullets, first_enemy); break;
            case 'd':
                move_spaceship_right(my_spaceship, map_size, bullets, first_enemy); break;
        }
        render_map(map_size, my_spaceship, bullets, first_enemy);
    }
    
}

void move_bullets(vector<Bullet> &bullets){

    int index_indicator = 0;

    for (Bullet &bullet : bullets){
        bullet.x--;

        if (bullet.x < 0){
            bullets.erase(bullets.begin() + index_indicator); continue;
        }
        index_indicator++;
    }
}


void move_spaceship_left(Spaceship &my_spaceship, vector<Bullet> &bullets, Enemy &enemy){
    if (my_spaceship.y > 0){
        my_spaceship.y--;

        Bullet new_bullet;
        new_bullet.x = my_spaceship.x - 1;
        new_bullet.y = my_spaceship.y;

        move_bullets(bullets);

        enemy.x++;

        bullets.push_back(new_bullet);
    }
}
void move_spaceship_right(Spaceship &my_spaceship, int &map_size, vector<Bullet> &bullets, Enemy &enemy){
    if (my_spaceship.y < map_size - 1){
        my_spaceship.y++;
        
        Bullet new_bullet;
        new_bullet.x = my_spaceship.x - 1;
        new_bullet.y = my_spaceship.y;

        move_bullets(bullets);

        enemy.x++;


        bullets.push_back(new_bullet);

        int index_indicator;

        bool flag = true;

        cout << enemy.x;
        cout << enemy.y;

        for (Bullet &bullet : bullets){
            for (int i = enemy.x; i < enemy.x + enemy.size; i++){
                for (int j = enemy.y; j < enemy.y + enemy.size; j++){
                    if (bullet.x == enemy.x && bullet.y == enemy.y){
                        enemy.heal--;
                        bullets.erase(bullets.begin() + index_indicator);
                        exit(0);
                        flag = false;
                    }
                }
            }
            if (flag){
                index_indicator++;
            }
            flag = true;
        }
    }
}

Enemy create_enemy(int &map_size){
    
    srand(time(0));

    Enemy new_enemy;

    int random_number = rand() % 4;

    switch(random_number){
        case 0:
            new_enemy.name = "Dart";
            new_enemy.size = 1;
            new_enemy.heal = 1;
            new_enemy.point = new_enemy.size * new_enemy.size;
            new_enemy.x = 0;
            new_enemy.y = rand() % map_size - new_enemy.size - 1;
            break;

        case 1:
            new_enemy.name = "Striker";
            new_enemy.size = 2;
            new_enemy.heal = 2;
            new_enemy.point = new_enemy.size * new_enemy.size;
            new_enemy.x = 0;
            new_enemy.y = rand() % map_size - new_enemy.size - 1;
            break;

        case 2:
            new_enemy.name = "Wraith";
            new_enemy.size = 3;
            new_enemy.heal = 4;
            new_enemy.point = new_enemy.size * new_enemy.size;
            new_enemy.x = 0;
            new_enemy.y = rand() % map_size - new_enemy.size - 1;
            break;

        case 3:
            new_enemy.name = "Banshee";
            new_enemy.size = 4;
            new_enemy.heal = 6;
            new_enemy.point = new_enemy.size * new_enemy.size;
            new_enemy.x = 0;
            new_enemy.y = rand() % map_size - new_enemy.size - 1;   
            break;    
    }

    return new_enemy;
}

void render_map(int &map_size, Spaceship &my_spaceship, vector<Bullet> &bullets, Enemy &enemy){
    int map[map_size][map_size] = {};
    
    map[my_spaceship.x][my_spaceship.y] = 1;

    for (Bullet &bullet : bullets){
        map[bullet.x][bullet.y] = 2;
    }

    for (int i = enemy.x; i < enemy.x + enemy.size; i++){
        for (int j = enemy.y; j < enemy.y + enemy.size; j++){
            map[i][j] = 3;
        }
    }


    system("cls");
    cout << enemy.heal << endl;
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