#include <SFML/Graphics.hpp>

#include <iostream>
#include <format>
#include <array>

// =================================
//      FIBONACCI
// =================================

int fibCount{ 0 };
int fibRecursiveCount{ 0 };
std::vector<int> fibCache{ 0, 1 };

int fibonacci(int n)
{
    fibCount++;
    if (n < fibCache.size())
    {
        return fibCache[n];
    }

    int value = fibonacci(n - 1) + fibonacci(n - 2);
    fibCache.push_back(value);

    return value;
}

int fibonacciRecursive(int n)
{
    fibRecursiveCount++;
    if (n <= 2)
        return 1;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// =================================
// PASCAL TRIANGLE - COMBINATIONS
// =================================

void printVector(std::vector<int> numbers)
{
    for (auto nr : numbers)
        std::printf(std::format("{}, ", nr).c_str());
    std::printf("\n");
}

template<int n>
void printArray(std::array<std::array<int, n>, n> numbers)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout << std::format("{0:3} ",numbers[i][j]);
        std::cout << '\n';
    }
}

std::vector<int> computePascalTriangle(int n)
{
    if (n == 1)
    {
        printVector({ 1 });
        return { 1 };
    }
    std::vector<int> solution = computePascalTriangle(n - 1);
    for (int i = solution.size() - 1; i > 0; i--)
    {
        solution[i] = solution[i] + solution[i - 1];
    }
    solution.push_back(1);
    printVector(solution);
    return solution;
}

int cnk(int n, int k)
{
    std::vector<int> result = computePascalTriangle(n+1);
    return result[k];
}

// ==========================
//      COMBINATIONS
// ==========================

int callsRecursive = 0;
int cnkRecursive(int n, int k)
{
    callsRecursive++;
    if (n <= 1 || k == 0 || n == k)
        return 1;
    return cnkRecursive(n - 1, k - 1) + cnkRecursive(n - 1, k);
}

const int n = 18;
const int k = 11;
std::array<std::array<int, 20>, 20> cnkCache{ 0 };
int callsDynamic = 0;

int cnkDynamic(int n, int k)
{
    callsDynamic++;
    if (k == 0 || n < 1 || n == k)
    {
        return cnkCache[n][k] = 1;
    }
    if (cnkCache[n][k] == 0)
        cnkCache[n][k] = cnkDynamic(n - 1, k - 1) + cnkDynamic(n - 1, k);
    return cnkCache[n][k];
}

long long factorial(int n)
{
    long long result{ 1 };
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

int cnkFactorial(int n, int k)
{
    return factorial(n) / (factorial(k) * factorial(n - k));
}

// ===========================================
//      NOTHING TO SEE HERE MOVE ALONG
// ===========================================

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // fibonacci

    std::cout << std::format("Fibonacci(30) recursive : {} - calls : {}\n", fibonacciRecursive(30), fibRecursiveCount);
    std::cout << std::format("Fibonacci(30) dynamic : {} - calls : {}\n", fibonacci(30), fibCount);

    std::cout << "\n";

    // combinations

    std::cout << std::format("Factorial C({}, {}) = {}\n", n, k, cnkFactorial(n, k));
	int c2 = cnk(n, k);
	std::printf(std::format("Pascal C({}, {}) = {}\n", n, k, c2).c_str());
	int c = cnkRecursive(n, k);

    std::cout << "\n";
	std::printf(std::format("Recursive C({}, {}) = {} with {} calls\n", n, k, c, callsRecursive).c_str());
	std::cout << std::format("Dynamic C({}, {}) = {} with {} calls\n", n, k, cnkDynamic(n, k), callsDynamic);
    printArray(cnkCache);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}