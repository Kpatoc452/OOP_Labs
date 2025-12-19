# Лабораторная работа №6: Паттерны проектирования

## Описание

Редактор подземелья для RPG игры Balagur Fate 3. Программа позволяет моделировать базовые локации, расставляя на них NPC (non-player characters).

## Вариант задания

**Типы NPC:**
- Орк (Orc)
- Странствующий рыцарь (Knight)
- Медведь (Bear)

**Правила боя:**
- Орки убивают медведей
- Медведи убивают рыцарей
- Рыцари убивают орков

## Реализованные паттерны

### 1. Factory (Фабрика)
- `NpcFactory` - создание NPC по типу
- `CreateFromString()` - загрузка NPC из файла по текстовому представлению типа

### 2. Visitor (Посетитель)
- `CombatVisitor` - базовый интерфейс посетителя
- `CombatResolver` - реализация боевой логики через паттерн Visitor
- Каждый тип NPC имеет метод `Accept()` для применения посетителя

### 3. Observer (Наблюдатель)
- `CombatObserver` - базовый интерфейс наблюдателя
- `ConsoleObserver` - вывод событий боя на консоль
- `FileObserver` - запись событий боя в файл
- `ObserverManager` - управление списком наблюдателей

## Структура проекта

```
6/
├── CMakeLists.txt       # Конфигурация сборки
├── main.cpp             # Основная демонстрация
├── example.cpp          # Пример боевой системы
├── include/             # Заголовочные файлы
│   ├── npc.hpp         # Базовый класс NPC
│   ├── orc.hpp         # Класс Орка
│   ├── knight.hpp      # Класс Рыцаря
│   ├── bear.hpp        # Класс Медведя
│   ├── factory.hpp     # Паттерн Factory
│   ├── visitor.hpp     # Паттерн Visitor
│   ├── observer.hpp    # Паттерн Observer
│   ├── editor.hpp      # Редактор подземелья
│   └── exceptions.hpp  # Исключения
├── src/                # Реализация
│   ├── npc.cpp
│   ├── orc.cpp
│   ├── knight.cpp
│   ├── bear.cpp
│   ├── factory.cpp
│   ├── visitor.cpp
│   ├── observer.cpp
│   └── editor.cpp
└── tests/              # Unit-тесты
    └── tests.cpp
```

## Функциональность

### Редактор поддерживает:

1. **Добавление NPC** с проверкой координат (0-500 метров) и уникальности имени
2. **Сохранение/загрузка** из файла
3. **Печать списка** всех NPC с типами, координатами и именами
4. **Боевой режим** с указанием дальности атаки
5. **Логирование событий** (консоль + файл)

## Сборка и запуск

### Сборка проекта:

```bash
cd 6
mkdir build
cd build
cmake ..
make
```

### Запуск программ:

```bash
# Основная демонстрация
./main

# Пример боевой системы
./example

# Запуск тестов
./tests
```

## Примеры использования

### Создание NPC через фабрику:

```cpp
auto orc = game::NpcFactory::Create(game::NpcType::ORC, "Grom", 100, 100);
auto knight = game::NpcFactory::CreateFromString("knight", "Arthur", 200, 200);
```

### Использование редактора:

```cpp
game::Editor editor;
editor.AddNpc(orc);
editor.AddNpc(knight);
editor.PrintNpcs();
editor.SaveToFile("dungeon.txt");
```

### Настройка наблюдателей:

```cpp
game::ObserverManager observer_manager;
observer_manager.Attach(std::make_shared<game::ConsoleObserver>());
observer_manager.Attach(std::make_shared<game::FileObserver>("log.txt"));
```

### Запуск боя:

```cpp
editor.StartCombat(50.0, observer_manager);  // Дальность 50 метров
```

## Тестирование

Проект содержит 32 unit-теста, покрывающих:
- Создание всех типов NPC
- Валидацию координат
- Работу фабрики
- Боевую систему (все комбинации типов)
- Паттерн Observer
- Функции редактора (добавление, удаление, сохранение, загрузка)

## Технологии

- **C++20**
- **CMake 3.10+**
- **GoogleTest v1.15.0** (для тестирования)
- **Address Sanitizer** (проверка утечек памяти)

## Принципы SOLID

Проект демонстрирует применение принципов SOLID:

- **S (Single Responsibility)**: каждый класс имеет одну ответственность
  - `Npc` - базовая функциональность NPC
  - `NpcFactory` - создание объектов
  - `Editor` - управление коллекцией NPC
  - `CombatResolver` - логика боя
  - `ObserverManager` - управление наблюдателями

- **O (Open/Closed)**: классы открыты для расширения, закрыты для модификации
  - Новые типы NPC добавляются наследованием от `Npc`
  - Новые типы наблюдателей от `CombatObserver`

- **L (Liskov Substitution)**: производные классы могут использоваться вместо базовых
  - Все NPC могут использоваться через указатель `Npc*`
  - Все наблюдатели через `CombatObserver*`

- **I (Interface Segregation)**: клиенты не зависят от неиспользуемых интерфейсов
  - `CombatVisitor` содержит только методы для обработки боя
  - `CombatObserver` только для уведомлений

- **D (Dependency Inversion)**: зависимость от абстракций, а не от конкретных классов
  - `Editor` работает с `NpcPtr` (shared_ptr<Npc>)
  - `ObserverManager` с `ObserverPtr` (shared_ptr<CombatObserver>)
