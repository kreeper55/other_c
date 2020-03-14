//  ��������� ��� ������ �����
typedef struct Player_log
{
    int size;           //  ������
    int* select_heap;   //  ��������� ����
    int* take_matches;  //  ������ ������
} Player_log;

//  ��� ������������� Player_log
Player_log init_player_log(const int size)
{
    Player_log player_log;
    player_log.size = size;
    //  �������� ������ ��� ������� ������ � size
    player_log.select_heap = (int*)malloc(size * sizeof(int));
    player_log.take_matches = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        //  ������ �� ��������� �������� = 0
        player_log.select_heap[i] = 0;
        player_log.take_matches[i] = 0;
    }
    return player_log;
}

//  ��� �������� �������
void clear_array(int* array)
{
    free(array);
    array = NULL;
}

//  ������� � ������������ ������ ���������� Player_log
void delete_player_log(Player_log* player_log)
{
    clear_array(player_log->select_heap);   //  ������� ������ ����
    clear_array(player_log->take_matches);  //  ������� ������� ������
    player_log->select_heap = NULL;         //  ������ �� ��������� �� NULL
    player_log->take_matches = NULL;
    free(player_log);   //  ���������� ������ player_log
    player_log = NULL;
}

//  ��������� ���������� ������ (�����)
void add_log(Player_log* player_log, const int heap, const int matches)
{
    player_log->size++; //  ����������� ������ � ������ �������� ������ ��� ��� �������
    player_log->select_heap = (int*)realloc(player_log->select_heap, player_log->size * sizeof(int));
    player_log->select_heap[player_log->size - 1] = heap;   //  ���������� ����� �������� � �����

    player_log->take_matches = (int*)realloc(player_log->take_matches, player_log->size * sizeof(int));
    player_log->take_matches[player_log->size - 1] = matches;
}
