# pipex

Цель проекта - реализация механизма UNIX - `pipe`.<br>

Для компиляции основной части программы необходимо запустить команду \
```make all```  <br>

Для компиляции бонусной части программы необходимо запустить команду \
```make bonus```  <br>

### Основная часть
Программа "pipex" должна повторять поведение следующей shell-команды
```bash
$> < file1 cmd1 | cmd2 > file2
```
и вызываться таким образом:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```

### Бонусная часть

Программе необходимо обрабатывать несколько пайпов:
```bash
$> < file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2

$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

И обработать "here_doc"
```bash
$> cmd << LIMITER | cmd1 >> file

$> ./pipex here_doc LIMITER cmd cmd1 file
```
