# HTTP HEAD Request via Raw Sockets (C Language)

Этот код демонстрирует отправку HTTP HEAD-запроса к серверу Google (www.google.se) с использованием сырых сокетов в Linux.

## Содержание
1. [Описание](#описание)
2. [Зависимости](#зависимости)
3. [Сборка](#сборка)
4. [Объяснение кода](#объяснение-кода)
5. [Аргументы функций](#аргументы-функций)
6. [Ограничения](#ограничения)
7. [Пример вывода](#пример-вывода)

---

## Описание
Программа выполняет:
1. Создание TCP-сокета.
2. Подключение к `www.google.se:80`.
3. Отправку HTTP-запроса `HEAD / HTTP/1.0`.
4. Получение и вывод ответа сервера.

---

## Зависимости
- Компилятор C (например, `gcc`).
- Linux-система (для работы с `<arpa/inet.h>`).

---

# Аргументы функций

### `socket(int domain, int type, int protocol)`
- **`domain`** (`AF_INET`)  
  Семейство адресов: IPv4.
- **`type`** (`SOCK_STREAM`)  
  Тип сокета: потоковый (TCP).
- **`protocol`** (`0`)  
  Протокол по умолчанию для TCP.

---

### `inet_addr(const char *cp)`
- **`cp`** (`"142.250.150.94"`)  
  Преобразует строку IPv4 в 32-битное число (сетевой порядок байт).

---

### `htons(uint16_t hostshort)`
- **`hostshort`** (`80`)  
  Конвертирует порт из хостового порядка байт в сетевой.

---

### `connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`
- **`sockfd`** (`s`)  
  Дескриптор сокета.
- **`addr`** (`(struct sockaddr*)&sock`)  
  Указатель на структуру `sockaddr_in` с адресом сервера.
- **`addrlen`** (`sizeof(sock)`)  
  Размер структуры адреса.

---

### `write(int fd, const void *buf, size_t count)`
- **`fd`** (`s`)  
  Дескриптор сокета.
- **`buf`** (`data`)  
  Данные для отправки (`HEAD / HTTP/1.0\n\n`).
- **`count`** (`strlen(data)`)  
  Длина данных в байтах.

---

### `read(int fd, void *buf, size_t count)`
- **`fd`** (`s`)  
  Дескриптор сокета.
- **`buf`** (`buf`)  
  Буфер для сохранения полученных данных.
- **`count`** (`511`)  
  Максимальное количество байт для чтения.

---

### `close(int fd)`
- **`fd`** (`s`)  
  Дескриптор сокета для закрытия.

---

## Сборка
    make 
---

## Пример вывода
    gcc -Werror -Wextra -Wall sockets.c -o sockets
    # strace -f ./sockets
    ./sockets

    HTTP/1.0 200 OK
    Content-Type: text/html; charset=ISO-8859-1
    Content-Security-Policy-Report-Only: object-src 'none';base-uri 'self';script-src 'nonce-cqIo9FKCn2Pmxgle_XFdwQ' 'strict-dynamic' 'report-sample' 'unsafe-eval' 'unsafe-inline' https: 
    http:;report-uri https://csp.withgoogle.com/csp/gws/other-hp
    P3P: CP="This is not a P3P policy! See g.co/p3phelp for more info."
    Date: Sat, 10 May 2025 06:46:34 GMT
    Server: gws
    X-XSS-Protection: 0
    X-Frame-Options: SAMEORIGIN
    Expires: Sat, 10 May 2025 06:46:34
    rm -rf ./sockets
---
