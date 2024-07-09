# Evolving Ecosystem Simulation

## English

### Overview
This project simulates an evolving ecosystem using genetic algorithms and neural networks. It models a simple environment where creatures must navigate, find food, and reproduce to survive. The simulation demonstrates concepts of artificial life, machine learning, and evolutionary computation.

### Features
- Neural network-based creature intelligence
- Genetic algorithm for evolution
- Dynamic food spawning
- Population tracking over time

### Requirements
- C++17 compatible compiler
- Standard C++ libraries

### How to Compile and Run
1. Ensure you have a C++17 compatible compiler installed.
2. Open a terminal in the project directory.
3. Compile the program using:
   ```
   g++ -std=c++17 -O3 EvolvingEcosystemSimulationinC++.cpp -o ecosystem_simulation.exe
   ```
4. Run the compiled program:
   ```
   ./ecosystem_simulation.exe
   ```

### Output
- The program will display the population count for each day of the simulation.
- A CSV file named `ecosystem_data.csv` will be generated, containing day-by-day population data.

### Key Components
1. **Neural Network**: Represents the "brain" of each creature, determining its behavior.
2. **Creature**: Represents an individual in the ecosystem, with properties like energy and position.
3. **Environment**: Manages the ecosystem, including creatures and food sources.
4. **Genetic Algorithm**: Implemented through creature reproduction and mutation.

### Customization
You can modify the following parameters in the `main()` function:
- Initial number of creatures
- Initial number of food sources
- Number of simulation days

### License
This project is open-source and available under the MIT License.

---

## فارسی

### نمای کلی
این پروژه یک اکوسیستم در حال تکامل را با استفاده از الگوریتم‌های ژنتیک و شبکه‌های عصبی شبیه‌سازی می‌کند. این مدل یک محیط ساده را نشان می‌دهد که در آن موجودات باید برای بقا، حرکت کنند، غذا پیدا کنند و تولیدمثل کنند. این شبیه‌سازی مفاهیم زندگی مصنوعی، یادگیری ماشین و محاسبات تکاملی را نشان می‌دهد.

### ویژگی‌ها
- هوش موجودات مبتنی بر شبکه عصبی
- الگوریتم ژنتیک برای تکامل
- تولید پویای غذا
- پیگیری جمعیت در طول زمان

### نیازمندی‌ها
- کامپایلر سازگار با C++17
- کتابخانه‌های استاندارد C++

### نحوه کامپایل و اجرا
1. اطمینان حاصل کنید که یک کامپایلر سازگار با C++17 نصب شده است.
2. یک ترمینال در دایرکتوری پروژه باز کنید.
3. برنامه را با استفاده از دستور زیر کامپایل کنید:
   ```
   g++ -std=c++17 -O3 EvolvingEcosystemSimulationinC++.cpp -o ecosystem_simulation.exe
   ```
4. برنامه کامپایل شده را اجرا کنید:
   ```
   ./ecosystem_simulation.exe
   ```

### خروجی
- برنامه تعداد جمعیت را برای هر روز از شبیه‌سازی نمایش می‌دهد.
- یک فایل CSV به نام `ecosystem_data.csv` ایجاد می‌شود که حاوی داده‌های جمعیت روز به روز است.

### اجزای کلیدی
1. **شبکه عصبی**: نشان‌دهنده "مغز" هر موجود است و رفتار آن را تعیین می‌کند.
2. **موجود**: نشان‌دهنده یک فرد در اکوسیستم است، با ویژگی‌هایی مانند انرژی و موقعیت.
3. **محیط**: اکوسیستم را مدیریت می‌کند، شامل موجودات و منابع غذایی.
4. **الگوریتم ژنتیک**: از طریق تولیدمثل و جهش موجودات پیاده‌سازی شده است.

### سفارشی‌سازی
می‌توانید پارامترهای زیر را در تابع `()main` تغییر دهید:
- تعداد اولیه موجودات
- تعداد اولیه منابع غذایی
- تعداد روزهای شبیه‌سازی

### مجوز
این پروژه منبع-باز است و تحت مجوز MIT در دسترس است.
