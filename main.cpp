#include <iostream>
#include <random>
#include <vector>
constexpr int tamanhoArray{10};
int matriz[tamanhoArray][tamanhoArray];
std::default_random_engine engine{std::random_device{}()};
std::uniform_int_distribution<long> dist{0, 99};

int main()
{
    int sumPath{};

    for (size_t i = 0; i < tamanhoArray; ++i)
    {
        for (size_t j = 0; j < tamanhoArray; ++j)
        {
            matriz[i][j] = dist(engine);
            std::cout << matriz[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::vector<std::pair<int, int>> path, whitePath;
    /************Primeiro node ******************/
    path.push_back(std::make_pair(0, 0));
    sumPath += matriz[0][0];
    /********************************************/
    /************Segundo node ******************/

    std::pair<int, int> nodeAtual = path.at(path.size() - 1), nodeAnterior;
    std::pair<int, int> max{
        std::make_pair(nodeAtual.first + 1, nodeAtual.second)};

    if (matriz[nodeAtual.first][nodeAtual.second + 1] > matriz[max.first][max.second])
    {
        max = std::make_pair(nodeAtual.first, nodeAtual.second + 1);
    }
    path.push_back(max);
    sumPath += matriz[max.first][max.second];
    /********************************************/
    /************2+n nodes (Ate chegar ultima linha)***************/

    while ((nodeAtual = path.at(path.size() - 1)).first != tamanhoArray - 1)
    {
        nodeAnterior = path.at(path.size() - 2);
        std::pair<int, int> max{
            std::make_pair(nodeAtual.first + 1, nodeAtual.second)};
        if ((nodeAtual.second - 1 > 0) && (nodeAnterior.second != nodeAtual.second - 1) && matriz[nodeAtual.first][nodeAtual.second - 1] > matriz[max.first][max.second])
        {
            max = std::make_pair(nodeAtual.first, nodeAtual.second - 1);
        }
        if ((nodeAtual.second + 1 < tamanhoArray) && (nodeAnterior.second != nodeAtual.second + 1) && matriz[nodeAtual.first][nodeAtual.second + 1] > matriz[max.first][max.second])
        {
            max = std::make_pair(nodeAtual.first, nodeAtual.second + 1);
        }
        path.push_back(max);
        sumPath += matriz[max.first][max.second];
    }
    /**************************************************************/
    /************Ultima Linha***************/

    for (int i = path.at(path.size() - 1).second + 1; i < tamanhoArray; ++i)
    {
        sumPath += matriz[tamanhoArray - 1][i];
        path.push_back(std::make_pair(tamanhoArray - 1, i));
    }
    /***************************************************/

    /* Print path and sumPath */
    std::cout << "\nPath: ";
    for (auto &&i : path)
    {

        std::cout << matriz[i.first][i.second] << " ";
    }

    std::cout << "\nSoma: "
              << sumPath << std::endl;
}