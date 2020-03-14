//  структура для вывода логов
typedef struct Player_log
{
    int size;           //  размер
    int* select_heap;   //  выбранные кучи
    int* take_matches;  //  взятые спички
} Player_log;

//  для инициализации Player_log
Player_log init_player_log(const int size)
{
    Player_log player_log;
    player_log.size = size;
    //  выделяем память под массивы длиной в size
    player_log.select_heap = (int*)malloc(size * sizeof(int));
    player_log.take_matches = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        //  ставим им начальные значения = 0
        player_log.select_heap[i] = 0;
        player_log.take_matches[i] = 0;
    }
    return player_log;
}

//  для очищения массива
void clear_array(int* array)
{
    free(array);
    array = NULL;
}

//  удаляем и высвобождаем память занимаемой Player_log
void delete_player_log(Player_log* player_log)
{
    clear_array(player_log->select_heap);   //  удаляем массив кучи
    clear_array(player_log->take_matches);  //  удаляем массива спички
    player_log->select_heap = NULL;         //  кидаем им указатель на NULL
    player_log->take_matches = NULL;
    free(player_log);   //  свобождаем память player_log
    player_log = NULL;
}

//  процедура добавления данных (логов)
void add_log(Player_log* player_log, const int heap, const int matches)
{
    player_log->size++; //  увеличиваем размер и заного выделяем память под два массива
    player_log->select_heap = (int*)realloc(player_log->select_heap, player_log->size * sizeof(int));
    player_log->select_heap[player_log->size - 1] = heap;   //  записываем новые значения в конец

    player_log->take_matches = (int*)realloc(player_log->take_matches, player_log->size * sizeof(int));
    player_log->take_matches[player_log->size - 1] = matches;
}
