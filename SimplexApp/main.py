from Simplex import SimplexMethod

def main():
    try:
        print("Загрузка данных из файла: task.txt")
        simplex = SimplexMethod("task.txt")
        
        print("=" * 60)
        print("НАЧАЛО РЕШЕНИЯ ЗАДАЧИ ЛИНЕЙНОГО ПРОГРАММИРОВАНИЯ")
        print("=" * 60)
        
        # Первая фаза - нахождение начального допустимого решения
        simplex.first_phase()
        
        # Вторая фаза - оптимизация целевой функции
        simplex.second_phase()
        
        print("=" * 60)
        print("РЕШЕНИЕ ЗАВЕРШЕНО")
        print("=" * 60)
        
    except FileNotFoundError:
        print("Ошибка: Файл task.txt не найден")
        print("Создайте файл с данными или укажите правильный путь")
    except Exception as e:
        print(f"Ошибка при выполнении симплекс-метода: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()