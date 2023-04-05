#include "Menu.cpp"

int main() {
    bool to_continue;
    to_continue = Init();
    if (!to_continue)
        return 0;
    std::cout << std::endl;
    auto graph = Input();
    std::cout << std::endl;
    do {
        to_continue = Menu(graph);
        std::cout << std::endl;
    } while (to_continue);
}
