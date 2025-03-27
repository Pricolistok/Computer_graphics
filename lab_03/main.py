import matplotlib.pyplot as plt


def create_graphic(stairs, title, name_of_picture):
    angles = [x for x in range(0, 91, 5)]
    plt.xlabel('Углы наклона в градусах')
    plt.ylabel('Количество ступенек для отрезка длиной 1000')
    plt.title(title)
    plt.plot(angles, stairs)
    plt.xticks(angles)
    plt.savefig("pictures/" + name_of_picture)

def create_one_graphic(stairs1, stairs2, stairs3, stairs4, stairs5):
    angles = [x for x in range(0, 91, 5)]
    plt.xlabel('Углы наклона в градусах')
    plt.ylabel('Количество ступенек')
    plt.title("Исследование ступенчатости.\n1000 - длина отрезка")
    plt.plot(angles, stairs1, linestyle='--', color='blue', marker='o', markersize=5, label="ЦДА")
    plt.plot(angles, stairs2, linestyle='-.', color='red', marker='s', markersize=5, label="Брензенхем (действ. коэф.)")
    plt.plot(angles, stairs3, linestyle='-', color='green', marker='^', markersize=5, label="Брензенхем (цел. коэф.)")
    plt.plot(angles, stairs4, linestyle=':', color='purple', marker='d', markersize=5, label="Брензенхем (уст. ступ.)")
    plt.plot(angles, stairs5, linestyle=':', color='orange', marker='x', markersize=5, label="ВУ")
    plt.legend()
    plt.xticks(angles)
    plt.savefig("pictures/all_in_one")


def main():
    with open("data_stair.txt", "r") as file:
        line1 = file.readline()
        create_graphic(list(map(int, line1.split())), "ЦДА", "CDA")
        line2 = file.readline()
        create_graphic(list(map(int, line2.split())), "Брензенхем с действительными коэфициентами", "BRENZENHEM_FLOAT")
        line3 = file.readline()
        create_graphic(list(map(int, line3.split())), "Брензенхем с целыми коэфициентами","BRENZENHEM_INT")
        line4 = file.readline()
        create_graphic(list(map(int, line4.split())), "Брензенхем с устр. ступенчатости", "BRENZENHEM_STAIR")
        line5 = file.readline()
        create_graphic(list(map(int, line5.split())), "ВУ", "WU")
        create_one_graphic(list(map(int, line1.split())), list(map(int, line2.split())), list(map(int, line3.split())), list(map(int, line4.split())), list(map(int, line5.split())))

    with open("data_time.txt") as file:
        line1 = list(map(float, file.readline().split()))
        line1 = sum(line1) / len(line1)  # Используем среднее значение
        line2 = list(map(float, file.readline().split()))
        line2 = sum(line2) / len(line2)
        line3 = list(map(float, file.readline().split()))
        line3 = sum(line3) / len(line3)
        line4 = list(map(float, file.readline().split()))
        line4 = sum(line4) / len(line4)
        line5 = list(map(float, file.readline().split()))
        line5 = sum(line5) / len(line5)
        x_data = ['ЦДА', 'Брензенхем с действительными коэфициентами', 'Брензенхем с целыми коэфициентами',
                  'Брензенхем с устр. ступенчатости', 'ВУ']
        y_data = [line1, line2, line3, line4, line5]
        plt.figure(figsize=(10, 14))
        plt.xticks(rotation=15, ha='right')
        plt.bar(x_data, y_data)

        plt.xlabel('Алгоритмы')
        plt.ylabel('Время (среднее)')
        plt.title('Гистограмма времени выполнения алгоритмов')
        plt.savefig("pictures/HIST_TIME.png")





if __name__ == "__main__":
    main()