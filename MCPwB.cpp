#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// Estructura que representa un tipo de leche
struct Milk {
    char typeOfMilk{};   // Tipo de leche (por ejemplo, 'A', 'B', 'C')
    float minimumQuota{};  // Cuota mínima requerida para el tipo de leche
    float profit{};        // Beneficio por litro de leche de este tipo
};

// Estructura que representa un nodo en el problema
struct Node {
    int number{};           // Número de nodo
    int coordinateX{};      // Coordenada X del nodo
    int coordinateY{};      // Coordenada Y del nodo
    float amountOfMilk{};   // Cantidad de leche en el nodo
    Milk typeOfMilk{};      // Tipo de leche en el nodo
};

// Estructura que representa un camión
struct Truck {
    int number{};               // Número identificador del camión
    float capacity{};           // Capacidad máxima del camión
    float amountOfMilk{};       // Cantidad de leche en el camión
    Milk typeOfMilk{};          // Tipo de leche en el camión
    vector<Node> route{};       // Ruta que sigue el camión
    double cost{};              // Costo acumulado de la ruta del camión
};

vector<Truck> trucks;           // Vector de camiones
vector<Milk> milks;             // Vector de tipos de leche
vector<Node> nodes;             // Vector de nodos (granjas y planta procesadora)

// Inicialización de funciones
// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
vector<Truck> twoOPTTwoRoutes(const vector<Truck> &vectorOfTruck, int firstTruck, int secondTruck, int firstRouteLimit,
                          int secondRouteLimit);
*/

bool equalByCapacity(const vector<int> &indexOfTrucks, const vector<Truck> &vectorOfTrucks,
                     const vector<vector<int>> &allPosibleOrderOfTruck);

vector<Truck>
greedy(vector<Truck> vectorOfTrucks, vector<Node> vectorOfNodes, const vector<int> &orderOfTrucks, int limit,
       bool considerCost);

bool milkMinimumQuota(const vector<Truck> &vectorOfTrucks, const vector<Node> &vectorOfNodes, const int &currentTruck,
                      const Node &nextNode);

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
bool milkMinimumQuotaAfter2opt(const vector<Truck> &vectorOfTrucks, const vector<Milk> &vectorOfMilks);
*/
bool isInList(const std::vector<int> &element, const std::vector<std::vector<int>> &list);

vector<Truck> HillClimbingAnyImprovement(vector<Truck> vectorOfTrucks, int limit);

vector<vector<int>> indexPermutation(const vector<Truck> &vectorOfTrucks);

double calculateProfit(const Truck &currentTruck, const Node &nextNode);

Milk whichTypeOfMilk(const Milk &truckMilk, const Milk &nodeMilk);

bool compareTrucksByTypeOfMilk(const Truck &a, const Truck &b);

Truck twoOPTOneRoute(const Truck &truck, int first, int last);

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
double compareNodeByMilkProfit(const Node &a, const Node &b);
*/

bool compareMilksByTypeOfMilk(const Milk &a, const Milk &b);

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
float calculateRouteAmountOfMilk(const vector<Node> &route);
*/

bool compareTrucksByNumber(const Truck &a, const Truck &b);

double totalProfit(const vector<Truck> &vectorOfTrucks);

vector<Truck> milkBlending(vector<Truck> trucksVector);

Truck swap(const Truck &truck, int first, int second);

double calculateCost(Node currentNode, Node nextNode);

double calculateRouteCost(const vector<Node> &route);

void results(const vector<Truck> &trucksVector);

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
Milk routeTypeOfMilk(const vector<Node> &route);
*/

int factorial(int number);

bool allNodesVisited(const vector<Truck> &vectorOfTrucks);

// Función para mostrar los resultados del problema
void results(const vector<Truck> &trucksVector) {
    double totalCost = 0, totalProfitPerMilk = 0;

    string data;

    // Calcular el costo total y el beneficio total por litro de leche
    for (const Truck &truck: trucksVector) {
        totalCost += truck.cost;
        totalProfitPerMilk += truck.amountOfMilk * truck.typeOfMilk.profit;
    }

    // Imprimir resultados
    cout << endl << totalProfitPerMilk - totalCost << "    " << totalCost << "    " << totalProfitPerMilk << endl << endl;
    for (const Truck &truck: trucksVector) {
        for (vector<Node>::size_type i = 0; i < truck.route.size(); i++) {
            cout << truck.route[i].number;
            if (i < truck.route.size() - 1) {
                cout << "-";
            }
        }
        cout << "   " << truck.cost << "   " << truck.amountOfMilk << " " << truck.typeOfMilk.typeOfMilk << endl;
    }
    cout << data << endl;
}


// Función que entrega el factorial de un número
int factorial(int number) {

    int temp = number - 1;
    int result = number;

    if (result <= 1) {
        return 1;
    }
    while (temp > 0) {
        result *= temp;
        temp--;
    }

    return result;
}

// Función que dice si un elemento vector<int> se encuentra en una lista vector<vector<int>>
bool isInList(const std::vector<int> &element, const std::vector<std::vector<int>> &list) {
    return any_of(list.begin(), list.end(), [&element](const std::vector<int> &i) {
        return i == element;
    });
}

// Función que nos dice si ya hay un orden en la lista de posible orden de camiones donde los camiones tengan la misma capacidad,
// es decir, que una solución generada por este orden no entregará un resultado distinto
bool equalByCapacity(const vector<int> &indexOfTrucks, const vector<Truck> &vectorOfTrucks,
                     const vector<vector<int>> &allPosibleOrderOfTruck) {
    for (vector<int> i: allPosibleOrderOfTruck) {
        for (int j = 0; j < static_cast<int>(vectorOfTrucks.size()); j++) {
            if (vectorOfTrucks[indexOfTrucks[j]].capacity != vectorOfTrucks[i[j]].capacity) {
                return false;
            }
        }
    }
    return true;
}

// Función que entrega una lista con todos los órdenes posibles en las que salen los camiones de la planta
vector<vector<int>> indexPermutation(const vector<Truck> &vectorOfTrucks) {
    int counterOfCombinations = 1;

    vector<int> candidateOrder = {};

    // Se guarda el número de posibles permutaciones entre el orden de los camiones
    int numberOfCombinations = factorial(static_cast<int>(vectorOfTrucks.size()));

    // Se crea una lista de los index de los camiones
    for (int i = 0; i < static_cast<int>(vectorOfTrucks.size()); i++) {
        candidateOrder.push_back(i);
    }

    // Se guarda el orden por defecto
    vector<vector<int>> orderOfTrucks;
    vector<vector<int>> infeasibleOrderOfTrucks;

    // Si el primer camión que sale, no tiene la capacidad de llevar la cuota mínima de leche de mejor tipo, entonces no dará solución factible
    if (vectorOfTrucks[candidateOrder[0]].capacity >= milks[0].minimumQuota) {
        orderOfTrucks = {candidateOrder};
    } else {
        infeasibleOrderOfTrucks = {candidateOrder};
    }

    while (counterOfCombinations < numberOfCombinations) {
        vector<int> tempList = candidateOrder;

        random_device rd;
        mt19937 gen(rd());

        // Se define la cantidad de números que se quiere elegir de la lista
        int numElementsToSelect = static_cast<int>(tempList.size());

        vector<int> randomElements;

        for (int i = 0; i < numElementsToSelect; i++) {

            // Se obtiene un elemento random entre 0 y el último index de la lista
            uniform_int_distribution<int> distribution(0, static_cast<int>(tempList.size()) - 1);
            int randomIndex = distribution(gen);

            // Se guarda un elemento aleatorio de la lista candidata y luego se elimina dicho elemento para no volver a elegirlo
            randomElements.push_back(tempList[randomIndex]);
            tempList.erase(tempList.begin() + randomIndex);
        }

        // Se verifica que el orden no haya sido guardado antes
        if (!isInList(randomElements, orderOfTrucks) and !isInList(randomElements, infeasibleOrderOfTrucks)) {
            // Si el primer camión que sale, no tiene la capacidad de llevar la cuota mínima de leche de mejor tipo, entonces no dará solución factible
            if (trucks[randomElements[0]].capacity >= milks[0].minimumQuota and
                !equalByCapacity(randomElements, trucks, orderOfTrucks)) {
                // Se guarda el orden de los camiones
                orderOfTrucks.push_back(randomElements);
            } else {
                infeasibleOrderOfTrucks.push_back(randomElements);
            }
            counterOfCombinations++;
        }

    }
    return orderOfTrucks;
}


// Función de comparación para ordenar leche por tipo de leche
bool compareMilksByTypeOfMilk(const Milk &a, const Milk &b) {
    return a.profit < b.profit;
}

// Función de comparación para ordenar camiones por tipo de leche
bool compareTrucksByTypeOfMilk(const Truck &a, const Truck &b) {
    return a.typeOfMilk.profit < b.typeOfMilk.profit;
}

// Función de comparación para ordenar camiones por número
bool compareTrucksByNumber(const Truck &a, const Truck &b) {
    return a.number < b.number;
}

// Función que entrega el profit final
double totalProfit(const vector<Truck> &vectorOfTrucks) {
    double profit = 0;
    double cost = 0;

    // Calcular el costo total y el beneficio total por litro de leche
    for (const Truck &truck: vectorOfTrucks) {
        profit += truck.amountOfMilk * truck.typeOfMilk.profit;
        cost += truck.cost;
    }

    return profit - cost;
}

// Función que verifica si hay mezclas de leche en la planta
vector<Truck> milkBlending(vector<Truck> trucksVector) {

    sort(trucksVector.begin(), trucksVector.end(), compareTrucksByTypeOfMilk);

    int truckSize = static_cast<int>(trucksVector.size());

    // Se verifica si hay mezclas en la planta
    for (int i = 0; i < truckSize; i++) {
        float left = trucksVector[i].amountOfMilk - trucksVector[i].typeOfMilk.minimumQuota;
        for (int k = i + 1; left < 0 and k < truckSize; k++) {
            if (trucksVector[k].typeOfMilk.profit > trucksVector[i].typeOfMilk.profit and
                trucksVector[k].amountOfMilk > trucksVector[k].typeOfMilk.minimumQuota) {
                float rest = trucksVector[k].amountOfMilk - trucksVector[k].typeOfMilk.minimumQuota;
                if (rest + left <= 0) {
                    left += rest;
                    trucksVector[i].amountOfMilk += rest;
                    trucksVector[k].amountOfMilk -= rest;
                } else {
                    trucksVector[i].amountOfMilk -= left;
                    trucksVector[k].amountOfMilk += left;
                    left = 0;
                }

            }
        }
    }

    sort(trucksVector.begin(), trucksVector.end(), compareTrucksByNumber);

    return trucksVector;

}


// Función que verifica si todos los nodos han sido visitados
bool allNodesVisited(const vector<Truck> &vectorOfTrucks) {
    int sumOfNodesPerRoute = 0;
    for (const Truck &i: vectorOfTrucks) {
        sumOfNodesPerRoute += static_cast<int>(i.route.size()) - 2;
    }
    if (static_cast<int>(nodes.size()) == sumOfNodesPerRoute + 1) {
        return true;
    }
    return false;
}

// Función para determinar el tipo de leche va a quedar después de la mezcla
Milk whichTypeOfMilk(const Milk &truckMilk, const Milk &nodeMilk) {
    if ((truckMilk.profit < nodeMilk.profit and truckMilk.typeOfMilk) or !nodeMilk.typeOfMilk) {
        return (truckMilk);
    } else {
        return (nodeMilk);
    }
}

// Función para calcular el costo entre dos nodos con base en la distancia euclidiana
double calculateCost(Node currentNode, Node nextNode) {
    double distanceX = (currentNode.coordinateX - nextNode.coordinateX);
    double distanceY = (currentNode.coordinateY - nextNode.coordinateY);
    return sqrt(pow(distanceX, 2) + pow(distanceY, 2));
}

// Función para calcular el beneficio al llegar a un nodo
double calculateProfit(const Truck &currentTruck, const Node &nextNode) {
    if (currentTruck.typeOfMilk.typeOfMilk) {
        return nextNode.amountOfMilk * currentTruck.typeOfMilk.profit;
    }
    return nextNode.amountOfMilk * nextNode.typeOfMilk.profit;
}

double calculateRouteCost(const vector<Node> &route) {
    double cost = 0;

    // Calcular el costo total y el beneficio total por litro de leche
    for (int i = 0; i < static_cast<int>(route.size()) - 1; i++) {
        cost += calculateCost(route[i], route[i + 1]);
    }
    return cost;
}

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
float calculateRouteAmountOfMilk(const vector<Node> &route) {
    float amount = 0;
// Calcular el costo total y el beneficio total por litro de leche
    for (const auto &i: route) {
        amount += i.amountOfMilk;
    }
    return amount;
}
*/

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
double compareNodeByMilkProfit(const Node &a, const Node &b) {
    if (!a.typeOfMilk.typeOfMilk or !b.typeOfMilk.typeOfMilk) {
        return a.typeOfMilk.profit > b.typeOfMilk.profit;
    } else {
        return a.typeOfMilk.profit < b.typeOfMilk.profit;
    }
}
*/

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
Milk routeTypeOfMilk(const vector<Node> &route) {
    vector<Node> temp = route;
    sort(temp.begin(), temp.end(), compareNodeByMilkProfit);
    return temp[0].typeOfMilk;
}
*/

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
bool milkMinimumQuotaAfter2opt(const vector<Truck> &vectorOfTrucks, const vector<Milk> &vectorOfMilks) {
    vector<Truck> tempTrucks = vectorOfTrucks;
    vector<Milk> tempMilks = vectorOfMilks;

    sort(tempTrucks.begin(), tempTrucks.end(), compareTrucksByTypeOfMilk);
    reverse(tempTrucks.begin(), tempTrucks.end());

    sort(tempMilks.begin(), tempMilks.end(), compareMilksByTypeOfMilk);
    reverse(tempMilks.begin(), tempMilks.end());

    float amountOfMilk = 0;

    for (Milk &milk: tempMilks) {
        for (Truck &truck: tempTrucks) {
            if (truck.typeOfMilk.typeOfMilk == milk.typeOfMilk) {
                amountOfMilk += truck.amountOfMilk;
            }
        }
        if (amountOfMilk >= milk.minimumQuota) {
            amountOfMilk -= milk.minimumQuota;
        } else {
            return false;
        }
    }
    return true;
}
*/

// Función para verificar si se cumple la cuota mínima de leche
bool milkMinimumQuota(const vector<Truck> &vectorOfTrucks, const vector<Node> &vectorOfNodes, const int &currentTruck,
                      const Node &nextNode) {
    Milk currentMilk = whichTypeOfMilk(vectorOfTrucks[currentTruck].typeOfMilk, nextNode.typeOfMilk);
    float milkAmount = 0;
    // lastMilkAmount se añade para verificar que toda la leche de menor calidad quepa en un solo camión
    float lastMilkAmount = 0;
    // Se recorren todos los tipos de leche
    for (auto &milk: milks) {
        float amountPerMilk = 0;
        // Se suma la leche del camión que tenga ese tipo de leche
        for (auto &truck: vectorOfTrucks) {
            if (truck.number != vectorOfTrucks[currentTruck].number and
                truck.typeOfMilk.typeOfMilk == milk.typeOfMilk) {
                milkAmount += truck.amountOfMilk;
                amountPerMilk += truck.amountOfMilk;
            }
        }
        // Se suma la leche de los nodos que tengan ese tipo de leche, y que aún no hayan sido visitados
        for (auto &node: vectorOfNodes) {
            if (node.number != nextNode.number and node.typeOfMilk.typeOfMilk == milk.typeOfMilk) {
                milkAmount += node.amountOfMilk;
                amountPerMilk += node.amountOfMilk;
                if (milks[milks.size() - 1].typeOfMilk == milk.typeOfMilk) {
                    lastMilkAmount += node.amountOfMilk;
                }
            }
        }
        // Se suma la leche del camión actual y del nodo al que se quiere ir, con base en la leche que queda después de la mezcla
        if (currentMilk.typeOfMilk == milk.typeOfMilk) {
            milkAmount += nextNode.amountOfMilk + vectorOfTrucks[currentTruck].amountOfMilk;
            amountPerMilk += nextNode.amountOfMilk + vectorOfTrucks[currentTruck].amountOfMilk;
            if (milks[milks.size() - 1].typeOfMilk == milk.typeOfMilk) {
                lastMilkAmount += nextNode.amountOfMilk + vectorOfTrucks[currentTruck].amountOfMilk;
                if (lastMilkAmount > vectorOfTrucks[currentTruck].capacity) {
                    return false;
                }
            }
        }
        // Si milkAmount > milk.minimumQuota, significa que, hay leche de sobra para poder mezclar con leche de menor calidad en la planta
        // si amountPerMilk es 0, significa que falta una de las leches, ya que, aunque tenga un tipo de leche de mayor
        // calidad que pueda cumplir con la cuota minima, no me sirve de nada si no tengo con que mezclarla
        milkAmount -= milk.minimumQuota;
        if (milkAmount < 0 or amountPerMilk == 0) {
            return false;
        }
    }
    return true;
}

// Función para resolver el problema usando un enfoque greedy
// vectorOfTrucks: vector de camiones
// vectorOfNodes: vector de granjas a las que los camiones pueden ir
// orderOfTrucks: vector de índices que indican el orden en el que iran los camiones
// limit: limite de iteraciones para encontrar una solución
// considerCost: Bool que define que criterio usar en la función miope (profit) o (profit-costo)
vector<Truck>
greedy(vector<Truck> vectorOfTrucks, vector<Node> vectorOfNodes, const vector<int> &orderOfTrucks, int limit,
       bool considerCost) {
    sort(milks.begin(), milks.end(), compareMilksByTypeOfMilk);
    reverse(milks.begin(), milks.end());

    int currentMilk = 0;
    for (int currentTruck: orderOfTrucks) {
        // Se añade el primer nodo (Planta)
        vectorOfTrucks[currentTruck].route.push_back(nodes[0]);

        int indexOfNode = 0;

        Node nextNode, currentNode = vectorOfNodes[0];

        bool stop = false;

        int counter = 0;
        while (!stop and counter < limit) {
            double profit = -10000, cost = 10000;


            for (int i = 1; i < static_cast<int>(vectorOfNodes.size()); i++) {
                // Se revisan todos los nodos que no hayan sido visitados y que cumplan con las restricciones
                if (currentNode.number != vectorOfNodes[i].number and
                    vectorOfNodes[i].typeOfMilk.profit >= milks[currentMilk].profit and
                    (vectorOfTrucks[currentTruck].amountOfMilk + vectorOfNodes[i].amountOfMilk <=
                     vectorOfTrucks[currentTruck].capacity) and
                    milkMinimumQuota(vectorOfTrucks, vectorOfNodes, currentTruck, vectorOfNodes[i])) {

                    double candidateProfit = calculateProfit(vectorOfTrucks[currentTruck], vectorOfNodes[i]);
                    double candidateCost = calculateCost(currentNode, vectorOfNodes[i]);

                    // Se utiliza un criterio de maximización de ganancia para elegir el nodo siguiente
                    if (((candidateProfit - candidateCost) > (profit - cost) and considerCost) or
                        (candidateProfit > profit and !considerCost)) {
                        nextNode = vectorOfNodes[i];
                        indexOfNode = i;
                        profit = candidateProfit;
                        cost = candidateCost;
                    }
                }
            }

            // Si se encontró un nuevo nodo al cual ir, se añade el nodo a la ruta
            // En caso contrario, se regresa a la planta y se termina el loop
            if (nextNode.number != currentNode.number) {

                vectorOfTrucks[currentTruck].amountOfMilk += nextNode.amountOfMilk;
                vectorOfTrucks[currentTruck].typeOfMilk = whichTypeOfMilk(currentNode.typeOfMilk,
                                                                          nextNode.typeOfMilk);
                vectorOfTrucks[currentTruck].cost += cost;
                vectorOfTrucks[currentTruck].route.push_back(nextNode);

                // Una vez añadido el nodo a la ruta, se elimina del vector de nodos para no visitarlo de nuevo
                vectorOfNodes.erase(vectorOfNodes.begin() + indexOfNode);

                currentNode = nextNode;

            } else {
                vectorOfTrucks[currentTruck].cost += calculateCost(
                        vectorOfTrucks[currentTruck].route[vectorOfTrucks[currentTruck].route.size() - 1],
                        vectorOfNodes[0]);
                vectorOfTrucks[currentTruck].route.push_back(vectorOfNodes[0]);
                stop = true;
            }
            counter++;
        }
        currentMilk++;
        // Si todos los nodos ya fueron visitados, entonces se encontró una solución
        if (allNodesVisited(vectorOfTrucks)) {
            break;
        }
    }
    return vectorOfTrucks;
}

// Función que aplica el movimiento 2-opt en la ruta de un camión
Truck twoOPTOneRoute(const Truck &truck, int first, int last) {
    Truck tempTruck = truck;
    reverse(tempTruck.route.begin() + first, tempTruck.route.end() - last);
    tempTruck.cost = calculateRouteCost(tempTruck.route);
    return tempTruck;
}

// No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando el movimiento 2op para 2 rutas
/*
vector<Truck> twoOPTTwoRoutes(const vector<Truck> &vectorOfTruck, int firstTruck, int secondTruck, int firstRouteLimit,
                              int secondRouteLimit) {

    vector<Truck> temp = vectorOfTruck;

    vector<Node> firstTruckLeftSubRoute(temp[firstTruck].route.begin(),
                                        temp[firstTruck].route.begin() + firstRouteLimit);

    vector<Node> secondTruckLeftSubRoute(temp[secondTruck].route.begin(),
                                         temp[secondTruck].route.begin() + secondRouteLimit);

    vector<Node> firstTruckRightSubRoute(temp[firstTruck].route.begin() + firstRouteLimit,
                                         temp[firstTruck].route.end());

    vector<Node> secondTruckRightSubRoute(temp[secondTruck].route.begin() + secondRouteLimit,
                                          temp[secondTruck].route.end());

    firstTruckLeftSubRoute.insert(firstTruckLeftSubRoute.end(), secondTruckRightSubRoute.begin(),
                                  secondTruckRightSubRoute.end());
    secondTruckLeftSubRoute.insert(secondTruckLeftSubRoute.end(), firstTruckRightSubRoute.begin(),
                                   firstTruckRightSubRoute.end());

    temp[firstTruck].route = firstTruckLeftSubRoute;
    temp[firstTruck].amountOfMilk = calculateRouteAmountOfMilk(temp[firstTruck].route);
    temp[firstTruck].cost = calculateRouteCost(temp[firstTruck].route);
    temp[firstTruck].typeOfMilk = routeTypeOfMilk(temp[firstTruck].route);


    temp[secondTruck].route = secondTruckLeftSubRoute;
    temp[secondTruck].amountOfMilk = calculateRouteAmountOfMilk(temp[secondTruck].route);
    temp[secondTruck].cost = calculateRouteCost(temp[secondTruck].route);
    temp[secondTruck].typeOfMilk = routeTypeOfMilk(temp[secondTruck].route);


    return temp;
}
*/

// Función que aplica el movimiento swap entre 2 nodos de una ruta
Truck swap(const Truck &truck, int first, int second) {
    Truck tempTruck = truck;
    Node tempNode = tempTruck.route[first];
    tempTruck.route[first] = tempTruck.route[second];
    tempTruck.route[second] = tempNode;
    tempTruck.cost = calculateRouteCost(tempTruck.route);
    return tempTruck;
}

vector<Truck> HillClimbingAnyImprovement(vector<Truck> vectorOfTrucks, int limit) {
    vector<Truck> candidateVectorOfTrucks = vectorOfTrucks;
    bool best = false;


    // Primer movimiento 2-OPT entre 2 rutas
    // No quedó en la versión final, ya que ninguna instancia obtuvo ganancias usando este movimiento
    /*
    for (int counter = 0; counter < limit and !best; counter++) {
    bool better = false;


    bool firstTruckReversed;
    bool secondTruckReversed;

    for (int i = 0; i < static_cast<int>(candidateVectorOfTrucks.size() - 1) and !better; i++) {
        for (int j = i + 1; j < static_cast<int>(candidateVectorOfTrucks.size()) and !better; j++) {
            firstTruckReversed = false;
            secondTruckReversed = false;
            for (int k = 1; k < static_cast<int>(candidateVectorOfTrucks[i].route.size()) and !better; k++) {
                for (int l = 1; l < static_cast<int>(candidateVectorOfTrucks[j].route.size()); l++) {
                    candidateVectorOfTrucks = twoOPTTwoRoutes(candidateVectorOfTrucks, i, j, k, l);
                    double candidateProfit = 0;
                    double currentProfit = 0;
                    better = true;
                    for (const Truck &truck: candidateVectorOfTrucks) {
                        if (truck.amountOfMilk <= truck.capacity) {
                            candidateProfit += truck.amountOfMilk * truck.typeOfMilk.profit;
                        } else {
                            better = false;
                            break;
                        }
                    }
                    for (const Truck &truck: vectorOfTrucks) {
                        currentProfit += truck.amountOfMilk * truck.typeOfMilk.profit;
                    }

                    if (better and candidateProfit > currentProfit and
                        milkMinimumQuotaAfter2opt(candidateVectorOfTrucks, milks)) {
                        vectorOfTrucks = candidateVectorOfTrucks;
                        break;
                    }
                    candidateVectorOfTrucks = vectorOfTrucks;
                    better = false;

                    if (!secondTruckReversed and
                        l == static_cast<int>(candidateVectorOfTrucks[j].route.size()) - 1) {
                        vector<Node> tempRoute = candidateVectorOfTrucks[j].route;
                        reverse(tempRoute.begin(), tempRoute.end());
                        candidateVectorOfTrucks[j].route = tempRoute;
                        secondTruckReversed = true;
                        l = 1;
                    }
                }
                if (!firstTruckReversed and k == static_cast<int>(candidateVectorOfTrucks[i].route.size()) - 1) {
                    vector<Node> tempRoute = candidateVectorOfTrucks[i].route;
                    reverse(tempRoute.begin(), tempRoute.end());
                    candidateVectorOfTrucks[i].route = tempRoute;
                    firstTruckReversed = true;
                    k = 1;
                }
            }
        }
    }
    if (!better) {
        best = true;
    }
    }

    best = false;
    */

    // Se obtiene el vecindario utilizando el movimiento 2-opt para una ruta
    for (int counter = 0; counter < limit and !best; counter++) {

        bool better = false;
        for (int i = 0; i < static_cast<int>(candidateVectorOfTrucks.size()) and !better; i++) {
            for (int j = 1; j < static_cast<int>(candidateVectorOfTrucks[i].route.size() - 2) and !better; j++) {
                for (int k = static_cast<int>(candidateVectorOfTrucks[i].route.size() - 3); k > i and !better; k--) {
                    candidateVectorOfTrucks[i] = twoOPTOneRoute(vectorOfTrucks[i], j, k);
                    // Se revisa si hay una solución mejor en el vecindario a medida que se va creando
                    // En caso de que se encuentre una solución mejor, better cambia a true y se sale del bucle.
                    if (candidateVectorOfTrucks[i].cost < vectorOfTrucks[i].cost) {
                        better = true;
                        vectorOfTrucks[i] = candidateVectorOfTrucks[i];
                    }
                }
            }
        }
        // Si ya no se encuentra una solución mejor, se sale del bucle
        if (!better) {
            best = true;
        }
    }

    best = false;

    // Se obtiene el vecindario utilizando el movimiento swap entre nodos(no necesariamente adyacentes), para la ruta de cada camión
    for (int counter = 0; counter < limit and !best; counter++) {
        bool better = false;
        for (int i = 0; i < static_cast<int>(candidateVectorOfTrucks.size()) and !better; i++) {
            for (int j = 1; j < static_cast<int>(candidateVectorOfTrucks[i].route.size() - 1) and !better; j++) {
                for (int k = 1; k < static_cast<int>(candidateVectorOfTrucks[i].route.size() - 1) and !better; k++) {
                    if (j != k) {
                        candidateVectorOfTrucks[i] = swap(vectorOfTrucks[i], j, k);
                        // Se revisa si hay una solución mejor en el vecindario a medida que se va creando
                        // En caso de que se encuentre una solución mejor, better cambia a true y se sale del bucle.
                        if (candidateVectorOfTrucks[i].cost < vectorOfTrucks[i].cost) {
                            better = true;
                            vectorOfTrucks[i] = candidateVectorOfTrucks[i];
                        }
                    }
                }
            }
        }
        // Si ya no se encuentra una solución mejor, se sale del bucle
        if (!better) {
            best = true;
        }
    }

    sort(vectorOfTrucks.begin(), vectorOfTrucks.end(), compareTrucksByNumber);
    return (vectorOfTrucks);
}

int main(int argc, char *argv[]) {

    // Se verifica si se proporcionaron suficientes argumentos
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <ruta_instancia> <max_iteraciones>" << std::endl;
        return 1;
    }

    // Se obtienen los argumentos de la línea de comandos
    string routeInstance = argv[1];

    cout << endl << "Archivo: " << routeInstance << endl;

    int K = stoi(argv[2]);

    // Se registra el tiempo de inicio
    double startTime = clock();

    ifstream archivo(routeInstance); // Se abre el archivo para lectura

    if (archivo.is_open()) {
        int numberOfTrucks, numberOfMilks, numberOfNodes;

        // Se lee el número de camiones
        archivo >> numberOfTrucks;

        // Se lee la información de cada camión
        for (int i = 0; i < numberOfTrucks; i++) {
            Truck truck;
            archivo >> truck.capacity;
            truck.number = i;
            truck.amountOfMilk = 0;
            truck.cost = 0;
            trucks.push_back(truck);
        }

        // Se lee el número de tipos de leche
        archivo >> numberOfMilks;

        // Se lee la información de los tipos de leche
        string typesOfMilk = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < numberOfMilks; i++) {
            Milk milk;
            archivo >> milk.minimumQuota;
            milk.typeOfMilk = typesOfMilk[i];
            milks.push_back(milk);
        }
        for (int i = 0; i < numberOfMilks; i++) {
            archivo >> milks[i].profit;
        }

        // Se lee el número de nodos
        archivo >> numberOfNodes;

        for (int i = 0; i < numberOfNodes; i++) {
            Node node;
            archivo >> node.number >> node.coordinateX >> node.coordinateY;
            char typeOfMilk;
            archivo >> typeOfMilk;
            if (typeOfMilk != '-') {
                for (int j = 0; j < numberOfMilks; j++) {
                    if (milks[j].typeOfMilk == typeOfMilk) {
                        node.typeOfMilk = milks[j];
                    }
                }
            }

            archivo >> node.amountOfMilk;
            nodes.push_back(node);
        }

        vector<vector<int>> allPosiblesOrderOfTrucks = indexPermutation(trucks);

        vector<vector<Truck>> allInitialSolutions;

        vector<Truck> finalSolutionBeforeHCAM;
        vector<Truck> finalSolutionAfterHCAM;
        vector<Truck> finalSolutionAfterBlending;
        double currentFinalProfit = 0;

        bool profitCriterion = true;

        // Se ejecutan las iteraciones para encontrár todas las posibles soluciones
        for (int i = 0; i < static_cast<int>(allPosiblesOrderOfTrucks.size()); i++) {
            vector<Truck> posibleSolution = greedy(trucks, nodes, allPosiblesOrderOfTrucks[i], K, profitCriterion);

            // Si todos los nodos fueron visitados, se considera que se encontró una solución factible, por lo que se guarda dicha solución en un vector
            if (allNodesVisited(posibleSolution)) {

                // Se utiliza la técnica de Hill Climbing con alguna mejora a la solución inicial, también se aplica la mezcla de leche en caso de ser necesaria
                vector<Truck> posibleSolutionAfterHCAM = HillClimbingAnyImprovement(posibleSolution, K);
                vector<Truck> posibleSolutionAfterBlending = milkBlending(posibleSolutionAfterHCAM);
                double candidateFinalProfit = totalProfit(posibleSolutionAfterBlending);

                // En caso de ser la major solución hasta el momento, se guarda como solución final
                if (candidateFinalProfit > currentFinalProfit) {
                    finalSolutionBeforeHCAM = posibleSolution;
                    finalSolutionAfterHCAM = posibleSolutionAfterHCAM;
                    finalSolutionAfterBlending = posibleSolutionAfterBlending;
                    currentFinalProfit = candidateFinalProfit;
                }
            }
            if (i == static_cast<int>(allPosiblesOrderOfTrucks.size()) - 1 and profitCriterion) {
                i = 0;
                profitCriterion = false;
            }
        }

        if (finalSolutionAfterBlending.empty()) {
            cerr << "No se pudo encontrar una solución factible." << endl;
            return 0;
        }

        cout << endl << "Solución inicial: " << endl;

        // Se muestra el resultado de la solución inicial
        results(finalSolutionBeforeHCAM);

        cout << "Solución después de Hill-Climbing: " << endl;

        // Se muestra el resultado después del Hill Climbing
        results(finalSolutionAfterHCAM);

        if (currentFinalProfit != totalProfit(finalSolutionAfterHCAM)) {

            cout << "Solución final después de la mezcla: " << endl;

            // Se muestra el resultado después de la mezcla
            results(finalSolutionAfterBlending);
        }

        // Se registra el tiempo de finalización
        double endTime = clock();

        // Se calcula la duración en segundos
        double time = (double(endTime - startTime) / CLOCKS_PER_SEC);

        cout << "Tiempo total de ejecución: " << to_string(time) << "[s]" << endl << endl;

        /*
        double total = 0;
        for (const auto &milk: milks) {
            cout << "Tipo " << milk.typeOfMilk << ": ";
            double sum = 0;
            for (const auto &node: nodes) {
                if (node.typeOfMilk.typeOfMilk == milk.typeOfMilk) {
                    sum += node.amountOfMilk;
                }
            }
            cout << sum << endl;
            total += sum;
        }

        cout << "total: " << total << endl;

        */

        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return 0;
}
