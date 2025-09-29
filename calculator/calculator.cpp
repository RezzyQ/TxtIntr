#include <iostream>
#include <cmath>
#include <stdexcept>
#include <getopt.h>

double calculateLn(double x) {
    if (x <= 0) {
        throw std::invalid_argument("Ошибка: ln(x) определен только для x > 0");
    }
    return log(x);
}

double calculateLog(double base, double x) {
    if (base <= 0 || base == 1) {
        throw std::invalid_argument("Ошибка: основание логарифма должно быть > 0 и ≠ 1");
    }
    if (x <= 0) {
        throw std::invalid_argument("Ошибка: log(x) определен только для x > 0");
    }
    return log(x) / log(base);
}

void printHelp() {
    std::cout << "Использование:\n";
    std::cout << "  -o, --operation <операция>  Выберите операцию (ln или log)\n";
    std::cout << "  количество операндов для функции:\n";
    std::cout << "  ln - 1 (натуральный логарифм)\n";
    std::cout << "  log - 2 (логарифм по основанию)\n";
    std::cout << "  ВАЖНО: логарифмы определены только для положительных чисел!\n";
    std::cout << "         основание логарифма не может быть равно 1\n";
}

int main(int argc, char* argv[]) {
    int opt;
    int index;
    std::string operation;

    static struct option long_options[] = {
        {"operation", required_argument, 0, 'o'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "ho:", long_options, &index)) != -1) {
        switch (opt) {
            case 'o':
                operation = optarg;
                break;
            case 'h':
                printHelp();
                return 0;
            default:
                printHelp();
                return 1;
        }
    }

    if (operation.empty()) {
        printHelp();
        return 1;
    }

    if (operation == "ln" && argc - optind != 1) {
        std::cerr << "Ошибка: Неправильное количество операндов для ln.\n";
        return 1;
    }

    if (operation == "log" && argc - optind != 2) {
        std::cerr << "Ошибка: Неправильное количество операндов для log.\n";
        return 1;
    }

    try {
        if (operation == "ln") {
            double x = std::stod(argv[optind]);
            double result = calculateLn(x);
            std::cout << "ln(" << x << ") = " << result << std::endl;
        } else if (operation == "log") {
            double base = std::stod(argv[optind]);
            double x = std::stod(argv[optind + 1]);
            double result = calculateLog(base, x);
            std::cout << "log_" << base << "(" << x << ") = " << result << std::endl;
        } else {
            std::cerr << "Ошибка: Неизвестная операция.\n";
            return 1;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
