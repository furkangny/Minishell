<h1 align="center">
     MINISHELL
</h1>

### İçindekiler

1. **[Shell Program Yapıları](#1-shell-program-yapıları)**
     1. **[Lexer](#11-lexer)**
     2. **[Parser](#12-parser)**
     3. **[Executor](#13-executor)**
     4. **[PIPE '|'](#14-pipe)**
     5. **[AND Operatörü (&&)](#15-and-operatörü)**
     6. **[OR Operatörü (||)](#16-or-operatörü)**
     7. **[Çıkış Durumu ($?)](#17-çıkış-durumu)**
     8. **[PID](#18-pid)**
     9. **[Environments (ENV)](#19-env)**
     10. **[Export](#110-export)**
     11. **[Declare](#111-declare)**
     12. **[Echo](#112-echo)**
     13. **[File Descriptors](#113-file-descriptors)**
2. **[Shell Program Fonksiyonları](#2-shell-program-fonksiyonları)**
     1. **[Fork()](#21-fork)**
     2. **[Pipe()](#22-pipe)**
     3. **[Dup()](#23-dup)**
     4. **[Dup2()](#24-dup2)**
4. **[Çalışma Yapısı](#3-çalışma-yapısı)**
     1. **[Akış Şeması](#31-akış-şeması)**
     2. **[Fonksiyonlar](#32-fonksiyonlar)**
5. **[Redirections - Yönlendirmeler](#4-redirections)**
     1. **[Standart Input '<'](#41-standart-input)**
     2. **[Standart Output '>'](#42-standart-output)**
     3. **[Appending Redirected Output ">>"](#43-appending-redirected-output)**
     4. **[Here Documents '<<'](#44-here-documents)**
<br>

## 1. Shell Program Yapıları

<br>

### 1.1 Lexer
- Lexer, metin girdisini tararken belirli dilbilgisi kurallarına dayalı olarak metni analiz eder.
- Bash shell için lexer, girilen metni parçalara ayırır ve her parçayı birer **"token"** olarak tanımlar.
- Tokenler, komutlar, argümanlar, değişkenler, operatörler vb. gibi dilbilgisi yapılarını temsil eder.
- Lexer, metindeki karakterleri okur, bu karakterlerin anlamsal gruplara ayrılmasını sağlar ve daha sonra bu tokenlerin bir listesini oluşturur.
```
3 + 4 * 2
```
- Lexer, yukarıdaki örnekte her bir karakteri sırayla analiz eder ve sırasıyla "3", "+", "4", "*" ve "2" karakterlerini analiz edecektir.
- Lexer, karakter analizi sırasında dilbilgisel yapıları (tokenleri) tanır ve oluşturur.
- Tamsayı: "3", "4", "2"
- Operatör: "+", "*"
- Lexer tanımlanan tokenleri çıktı olarak sunar.

*INTEGER: "3"*

*OPERATOR: "+"*

*INTEGER: "4"*

OPERATOR: "*"
 
*INTEGER: "2"*

<br>

### 1.2 Parser
- Parser, lexer tarafından oluşturulan token listesini alır ve bu tokenlerin belirli bir dilbilgisi yapısını takip ettiğini kontrol eder.
- Parser, dilbilgisi kurallarını kullanarak tokenleri işler, onları sözdizimsel olarak doğru bir şekilde sıralar ve dilin gramerine uygun bir ağaç yapısı oluşturur.
- Bash shell için parser, komutların doğru bir şekilde düzenlenmesini, argümanların ve seçeneklerin doğru yerleştirilmesini ve işaretçilerin (örneğin; ifadelerin bitişini veya döngülerin başlangıcını belirten belirteçler) doğru kullanılmasını kontrol eder.

<br>

### 1.3 Executor
- Executor, parser tarafından oluşturulan dilbilgisi ağacını alır ve bu ağaçtaki her komut için bir işlem oluşturur.
- Bash shell için executor, komutları işletmek ve sonuçlarını elde etmekle sorumludur.
- Executor, komutları işletirken, değişkenleri değerlendirir, dosya işlemlerini gerçekleştirir, diğer programları çalıştırır ve gerektiğinde çıktıyı bir sonraki komuta yönlendirmek için boruları (pipe) oluşturur.
- Executor ayrıca koşullu ifadeleri değerlendirir, döngülerin döngü koşullarını kontrol eder ve program akışını yönetir.

<br>

### 1.4 Pipe
- Bir işlemin çıktısını doğrudan başka bir işlemin girişine yönlendirmek için kullanılır.
- Birden çok işlemi bir araya getirerek verimli bir şekilde çalışmalarını sağlar.
- Pipe, dikey çubuk '|' sembolü ile temsil edilir.
```
ls | grep ".txt"
```
- Bu komut "ls" komutunun çıktısındaki ".txt" uzantısına sahip olan dosyaları filtrelemek için "grep" komutunu kullanılır.
- "ls" komutu dosya listesini üretir ve bu çıktı "grep" komutuna geçirilir. Sonuç olarak, yalnızca ".txt" uzantısına sahip dosyalar ekrana yazdırılır.

<br>

### 1.5 AND Operatörü
- Komut satırında **'&&'** operatörü soldaki ifadeden sırasıyla çalışmaya başlar.
- Soldaki ifade başarılıysa sağındakileri çalıştırır.
```
git add . && git commit -m "commit" && git push
```
- Yukarıdaki örnekte "git commit -m" satırı çalışmazsa onun sağındaki komutlar da çalışmayacaktır.

<br>

### 1.6 OR Operatörü
- Komut satırında **'||'** operatörü yalnızca soldaki ifade başarısız ise sağındakini çalıştırır.
```
make || make fclean
```
```
gcc deneme.c || echo "Failed."
```


<br>

### 1.7 Çıkış Durumu
- Her bir komut çalıştırıldığında, çıkış durumu bir tam sayı değeriyle temsil edilir.
- Başarı durumunda genellikle 0 değeri döndürülür, hata durumunda ise farklı bir değer döndürülür.
- "$?" değişkeni, en son çalıştırılan komutun çıkış durumunu içerir.
```
echo a
$?
```
- Başarılı olduğu için '0' döner.
```
cat abc.txt
$?
```
- Böyle bir dosya olmadığı için '1' hata durumu döner.
```
/bin/ech0
$?
```
- Böyle bir komut bulamadığı için '127' döner.

<br>

### 1.8 Pid
- PID, çalışan bir işlemin **benzersiz kimliğini** temsil eder.
- Her işlem, işletim sistemi tarafından PID ile tanımlanan benzersiz bir numaraya sahiptir.
- PID, bir işlemin kimliğini takip etmek, işlemler arasında iletişim kurmak veya işlemi kontrol etmek için kullanılabilir.
```
pid_t pid = getpid();
```
- Bir işlemi sonlandırmak veya durdurmak istediğinizde PID'ye ihtiyaç duyarsınız. Ayrıca belirli bir işlemi izlemek veya diğer işlemlerle etkileşime geçmek için PID kullanabilirsiniz.
- Bir işlem başlamadıysa "pid" numarasının değeri "-1" olarak ayarlanır.

<br>

### 1.9 ENV
- Environment variables (Çevresel Değişkenler) sistemdeki programlar ve işlemler tarafından kullanılan değerlerdir.
- Bu değişkenler, çalışan programlara ve komutlara bazı bilgiler sağlamak için kullanılır.
- Bash, bu değişkenlere erişim sağlamak için çeşitli yöntemler sunar.
- Environment variables, **anahtar-değer (key-value)** çiftleridir.
- Anahtarlar değişkenlere erişmek için kullanılan isimlerdir ve değerler ise bu değişkenlerin taşıdığı bilgidir.
- Örneğin, bir "PATH" değişkeni, sistemdeki programların bulunduğu dizinlerin bir listesini içerebilir.
- Bir değişken tanımlamak için:
```
export MY_VARIABLE="Hello, World"
```
değişkenin adını belirtip buna bir değer atamanız gerekir. Bash'te bu işlem için genellikle 'export' komutu kullanılır.
- Bir değişkene erişmek için:
```
echo $MY_VARIABLE
```
**'$'** işaretini kullanarak değişken adını çağırabiliriz.
- Bir değişkeni silmek için:
```
unset MY_VARIABLE
```
- Bazı environment variables, sistem tarafından otomatik olarak tanımlanır ve kullanılabilir. Örneğin:
     - **'PATH'**: Sistemdeki programların bulunduğu dizinlerin listesi
     - **'HOME'**: Kullanıcının ana dizini
     - **'USER'**: Kullanıcının adı
- Bash, çeşitli öntanımlı environment variables sağlar. Örneğin:
     - **'PWD'**: Geçerli çalışma dizini
     - **'SHELL'**: Kullanılan kabul (shell) programının adı
     - **'LANG'**: Dil ayarı

<br>

### 1.10 Export
```
export
```
- **"export"** komutu, bir değişkeni kabuk ortamına (environment) aktarmak için kullanılır.
- Bir değişkeni **"export"** ettiğinizde, bu değişken ve değeri, alt kabuk süreçlerine aktarılır ve bu süreçlerde erişilebilir hale gelir.
- "export" komutu, genellikle çevre değişkenlerini (örneğin, PATH, HOME) veya kullanıcı tanımlı değişkenleri alt kabuk süreçlerinde kullanılabilir hale getirmek için kullanılır.
- Aktarılan değişkenler, alt kabuk süreçlerinde değiştirilebilir ve bu değişiklikler ebeveyn kabuk sürecini etkilemez. Yani, alt kabuk süreçlerinde yapılan değişiklikler yalnızca o süreçleri etkiler.
```
my_var="Hello"
export my_var
```
- Yukarıdaki örnekte, "my_var" adında bir değişken oluşturulur ve daha sonra "export" komutuyla kabuk ortamına aktarılır. Bu "my_var" değişkeninin alt kabuk süreçlerinde de erişilebilir hale gelmesini sağlar.

<br>

### 1.11 Declare
- **"declare"** komutu, değişkenlerin tanımlanması, türü belirlenmesi ve özelliklerinin atanması için kullanılır.
```
declare [options] variable=value
```
- Değişkenlerin türünü belirleyebilirsiniz. Örneğin, **"-i"** seçeneğiyle bir değişkeni tamsayı (integer) olarak tanımlayabilirsiniz.
- Değişkenlere özel nitelikler (readonly, local vb.) atayabilirsiniz.
- **"declare"** komutu, sadece tanımlandığı kabuk oturumu veya kabuk betiği içinde geçerli olan değişkenler oluşturmanıza olanak sağlar.
- Yani, alt kabuk süreçlerinde geçerli olmazlar.
```
declare -i num=10
```
- 'num' değişkeni tamsayı olarak tanımlanır.
```
declare -r readonly_var="Hello"
```
- 'readonly_var' değişkeni salt okunur olarak tanımlanır.
```
declare -x exported_var="World"
```
- 'exported_var' değişkeni kabuk ortamına aktarılır.
```
declare -a my_array=(1 2 3)
```
- 'my_array' değişkeni dizi olarak tanımlanır.
```
declare -f my_function
```
- 'my_function' isimli bir işlev tanımlanır.

<br>

### 1.12 Echo
- **'echo'**, bir metni ya da değişkenin değerini ekrana yazdırmak için kullanılan bir komuttur.
- **'-n'** seçeneği ise çıktının sonuna bir satır atlama karakteri (\n) eklememeyi sağlar.
```
name="Yakup"
echo "My name. is $name"
```
- Yukarıdaki örnekte, "name" adında bir değişken tanımlanır ve "echo" komutuyla değişkenin değeri ekrana yazdırılır. Çıktı olarak "My name is Yakup" ifadesini görürüz.
```
echo -n "Hello, " && echo "World"
```
- Yukarıdaki örnekte, **"-n"** seçeneği kullanılarak ilk "echo" komutunda satır atlama karakteri devre dışı bırakılır. İkinci "echo" komutu ise satır atlama karakteriyle birlikte çalışır ve çıktı olarak "Hello, World!" ifadesini görürürüz.
- **'&&'** operatörü Bash kabuğunda kullanılan bir mantıksal operatördür ve ardışık komutları birleştirmek için kullanılır.

<br>

### 1.13 File Descriptors
- Bash kabuğunda kullanılan dosya tanımlayıcıları (file descriptors) bir sürecin giriş, çıkış ve hata akışlarını yönlendirmek için kullanılan sayısal değerlerdir.
- İlk 3 file descriptor OS'a ayrılmıştır, gerisini kullanıcı doldurur.

#### 0: Standart Giriş (stdin):
- Standart giriş, bir sürece veri sağlayan mekanizmadır. Genellikle klavye veya başka bir süreç tarafından sağlanan girişe karşılık gelir.
- Dosya tanımlayıcısı 0 olarak kabul edilir.

#### 1: Standart Çıkış (stdout):
- Standart çıkış, bir sürecin çıktısını yönlendirdiği yerdir. Varsayılan olarak, standart çıktı, verilerin kabuk penceresine veua bir dosyaya yazdırılmasını sağlar.
- Dosya tanımlayıcısı 1 olarak temsil edilir.

#### 2: Standart Hata (stderr):
- Standart hata, bir sürecin hata ve hata mesajlarını yönlendirdiği yerdir.
- Genellikle standart çıktıdan ayrı tutulur ve hata ayıklama ve hata yönetimi için kullanılır.
- Dosya tanımlayıcısı 2 olarak temsil edilir.

#### 1. Standart Girişten Okuma:
```
read line
```
- Yukarıdaki komut, kullanıcıdan bir giriş satırı okur. Kullanıcıdan girilen veri, standart giriş (stdin) üzerinden alınır.

#### 2. Standart Çıktıya Yazdırma:
```
echo "Hello, World" > file.txt
```
- Yukarıdaki komut, "Hello, World" metnini "file.txt" dosyasına yazar. Standart çıktı (stdout) yönlendirilerek dosyaya veri yazılır.

#### 3. Standart Hata Çıktısını Yönlendirme:
```
command_not_found 2> error.log
```
- Yukarıdaki komut, mevcut olmayan bir komutu çalıştırmaya çalışır ve oluşan hata mesajını "error.log" dosyasına yazar. Standart hata (stderr), dosyaya yönlendirilerek hatalar kaydedilir.

<br>

## 2. Shell Program Fonksiyonları

<br>

### 2.1 Fork
- Fork() sistem çağrısı, yeni bir process oluşturmak için kullanılır.
- Bu işlem child process olarak adlandırılır ve fork() çağrısını yapan process(parent process) ile eş zamanlı olarak çalışır.
- Yeni bir child process oluşturulduktan sonra, her iki işlem de fork() sistem çağrısını takip eden bir sonraki komutu yürütür.
- Child process parent process ile aynı pc(program counter) aynı CPU registerlere ve aynı open files'lere sahiptir.
- Fork() işlemi herhangi bir parametre almaz ve bir tamsayı değeri döndürür.

![a](https://github.com/Yakupacs/Ecole42_Minishell/assets/73075252/29ba1dd6-d2c0-4631-a7c6-53efa91dd787)

| Dönüş Değeri  | Tanım |
| ------------- | ------------- |
| Negatif değer  | Child process oluşturma başarısız.  |
| Sıfır (0)  | Yeni bir child process oluşturuldu.  |
| Pozitif değer  | Yeni oluşturulan child process'in ID'sini içerir.  |

```
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 
int main(int argc, char *argv[]){
     int id = fork();
     if (id == 0){
          printf("Hello from child process\n");
     } else {
          printf("Hello from the main process\n");
     }
     return 0;
}
```

```
output:
     Hello from child process
     Hello from the main process
```


<br>

### 2.2 Pipe

- Pipe, bir işlemin standart çıkışının diğer bir sürecin standart girdisi haline geldiği iki process arasındaki bağlantıdır.
- Pipe, yalnızca tek yönlü iletişim sağlar. Yani bir process bir pipe'e yazarken diğer process pipe'den okur.
- Pipe "sanal dosya" olarak işlem gören ana bellekteki bir alanı açar.
- Bir process bu "sanal dosyaya" veya pipe'e yazabilirken, diğer ilişkili process ondan okuyabilir.
- Eğer bir process pipe'e bir şey yazılmadan önce okumaya çalışırsa, process yazılan bir şey olana kadar askıya alınır.

![pipe](https://github.com/Yakupacs/Ecole42_Minishell/assets/73075252/d2e1c274-ef21-4601-8daa-da16fc4767ec)

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd[2]; // fd[0] => Read, fd[1] => Write
    char buffer[20];

    if (pipe(fd) == -1) {
        perror("Pipe oluşturma hatası");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        close(fd[0]); // Read kapattı.
        char message[] = "Merhaba Ebeveyn!";
        write(fd[1], message, sizeof(message)); // Write(fd[1]) içerisinde "Merhaba Ebeveyn!"
        close(fd[1]); // Write kapattı.
    } else {
        // Parent process
        close(fd[1]); // Yazma kapattı.
        read(fd[0], buffer, sizeof(buffer)); // Read(fd[0]) içerisinden "Merhaba Ebeveyn" okudu.
        printf("Ebeveyn: %s\n", buffer);
        close(fd[0]);
    }

    return 0;
}
```

```
output:
     Ebeveyn: Merhaba Ebeveyn!
```

### 2.3 Dup

- dup() sistem çağrısı, bir dosya tanımlaycısının bir kopyasını oluşturur.
- Yeni tanımlayıcı için kullanılmayan en düşük numaralı tanımlayıcıyı kullanır.
- Kopya başarılı oluşturulursa, orijinal ve kopya dosya tanımlayıcıları birbirinin yerine kullanılabilir.
- Her ikisi de aynı açık dosya tanımına işaret eder ve bu nedenle dosya konumunu ve dosya durum bayraklarını paylaşırlar.

```
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
  
int main()
{
    int file_desc = open("dup.txt", O_WRONLY | O_APPEND);
      
    if(file_desc < 0)
        printf("Error opening the file\n");

    int copy_desc = dup(file_desc);

    write(copy_desc,"This will be output to the file named dup.txt\n", 46);
          
    write(file_desc,"This will also be output to the file named dup.txt\n", 51);

}
```
- Yukarıdaki kodda daha önceden oluşturulan dup.txt dosyası dup() fonksiyonu ile kopyalanarak iki dosya tanımlayıcısı tarafından kullanılır ve iki tanımlayıcı da dosyaya yazma işlemi yapabilir.

<br>

### 2.4 Dup2

- int dup2(int oldfd, int newfd);
- dup() fonksiyonu ile temel farkları, kullanıcının belirttiği tanımlayıcı numarasını kullanmak yerine kullanılmayan en düşük numaralı dosya tanımlayıcısını kullanmaktır.

```
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
  
int main()
{
    int fd = open("tricky.txt", O_WRONLY | O_APPEND, 0777);

    dup2(fd, 1) ; 
          
    printf("I will be printed in the file tricky.txt\n");
}
```
- Yukarıdaki kodda STDOUT = 1 oluşturulan fd tanımlayıcısına aktarılır ve STDOUT'a aktarılan çıktılar fd içerisine yazılır.

<br>

## 3. Çalışma Yapısı

<br>

### 3.1 Akış Şeması

![image](https://github.com/Yakupacs/Ecole42_Minishell/assets/73075252/95882bea-cef8-4113-9354-8da56ccaaa55)

<br>

### 3.2 Fonksiyonlar

| Fonksiyon  | Kütüphane | İşlev |
| ------------- | ------------- | ------------- |
| printf  | <stdio.h>  | Çıktıyı stdout'a yazdırır. |
| malloc  | <stdlib.h>  | Dinamik bellek ayırır. |
| free  | <stdlib.h>  | Dinamik belleği serbest bırakır. |
| read  | <unistd.h>  | Veriyi okur. |
| write  | <unistd.h>  | Veriyi yazar. |
| open  | <fcntl.h>  | Dosyayı açar. |
| close  | <unistd.h>  | Dosyayı kapatır. |
| fork  | <unistd.h>  | Yeni bir child process oluşturur. |
| wait  | <sys/wait.h>  | Bir child process işleminin tamamlanmasını bekler. |
| waitpid  | <sys/wait.h>  | Belirli bir child process işleminin tamamlanmasını bekler. |
| wait3  | <sys/wait.h>  | Bir child process işleminin tamamlanmasını bekler. |
| wait4  | <sys/wait.h>  | Belirli bir child process işleminin tamamlanmasını bekler. |
| signal  | <signal.h>  | Sinyal yakalayıcıyı ayarlar. |
| kill  | <signal.h>  | İşlemi sonlandırıp sinyal gönderir. |
| exit  | <stdlib.h>  | Programda çıkış yapar. |
| getcwd  | <unistd.h>  | Geçerli çalışma dizinini alır. |
| chdir  | <unistd.h>  | Çalışma dizinini değiştirir. |
| stat  | <sys/stat.h>  | Dosya veya dizin hakkında bilgi alır. |
| lstat  | <sys/stat.h>  | Sembolik bağlantının kendisi hakkında bilgi alır. |
| fstat  | <sys/stat.h>  | Dosya tanımlayıcısına bağlı dosya hakkında bilgi alır. |
| execve  | <unistd.h>  | Yeni bir program yürütür. |
| dup  | <unistd.h>  | Dosya tanımlayıcısını kopyalar. |
| dup2  | <unistd.h>  | Dosya tanımlayıcısını belirtilen dosya tanımlayıcısına kopyalar. |
| pipe  | <unistd.h>  | İki yönlü bir iletişim kanalı (pipe) oluşturur. |
| opendir  | <dirent.h>  | Dizin akışını açar. |
| readdir  | <dirent.h>  | Bir sonraki dizin girdisini okur. |
| closedir  | <dirent.h>  | Dizin akışını kapatır. |
| strerror  | <string.h>  | Hata numarasına karşılık gelen bir hata açıklaması döndürür. |
| errno  | <errno.h>  | Hata kodunu tutan bir değişken. |
| termcap  | <term.h>  | Terminal özelliklerini elde eder. |

<br>

## 4. Redirections

<br>

### 4.1 Standart Input

- "<" sembolü, bir dosyadan giriş almak için kullanılan bir yönlendirme işlemidir. Bu işlem, bir komutun girişini, belirtilen bir dosyanın içeriğiyle değiştirir.
- Bir komut çalıştırıldığında, genellikle kullanıcının klavyeden giriş yapması beklenir. Ancak '<' sembolü kullanılarak, komutun girişi belirli bir dosyadan alınabilir.
- Bu, komutun klavyeden giriş almak yerine, belirli bir dosyayı giriş olarak kullanmasını sağlar.

```
sort < dosya.txt
```
- Örneğin aşağıdaki komutta 'sort' komutunu çalıştırırken girişi "girdi.txt" adlı dosyadan alır. Yani, girdi.txt dosyasının içeriği sort komutunun girişi olarak kullanılır.
```
cat < dosya.txt
```
- Yukarıdaki kodda dosya.txt adlı dosyanın içeriği okunur.
```
grep "kelime" < arama.txt
```
- Yukarıdaki kodda bir komutun girdisini standart girdiden değil de bir dosyadan alır ve "kelime" stringini arama.txt adı dosyada arar.

<br>

### 4.2 Standart Output

- '>' sembolü, bir komutun çıktısını belirtilen bir dosyaya yönlendirmek için kullanılan bir yönlendirme işlemidir.
- Bu işlem, komutun çıktısını bir dosyaya yazarak, komutun normalde ekrana veya standart çıktıya yazdığı çıktıyı dosyaya kaydetmek için kullanılır.

```
ls > dosya.txt
```
- Bu komut, ls komutunu çalıştırırken, çıktısını dosya.txt adlı bir dosyaya yönlendirir. 
- Yani, ls komutunun normalde ekrana yazdığı dosya ve dizin listesi, bu sefer dosya.txt adlı dosyaya yazılır.
```
echo "Merhaba dünya" > dosya.txt
```
- Bu komut "Merhaba dünya" ifadesini dosya.txt adlı bir dosyaya yazar.

<br>

### 4.3 Appending Redirected Output

- ">>"
- Shell komut dosyalarında ve terminal komutlarında çıktıyı bir dosyaya eklemek için kullanılan bir yönlendirme işlemidir.
- Bu yöntem, bir komutum veya betiğin çıktısını bir dosyaya yazarken var olan bir dosyanın içeriğini korumak veya bir dosyaya ardışık çıktı eklemek için kullanılır.

```
echo "Yeni satır" >> dosya.txt
```
- Bu komut "Yeni satır" metnini "dosya.txt" adlı bir dosyaya ekleyecektir. Eğer dosya mevcut değilse oluşturulur.
- Eğer dosya zaten varsa "Yeni satır" metni mevcut içeriğin sonuna eklenir.
```
date >> log.txt
echo "Komut çalıştırıldı." >> log.txt
```
- Önce "date" komutunun çıktısı "log.txt" adlı bir dosyaya eklenir. Sonra da "Komut çalıştırıldı." metni aynı dosyanın sonuna eklenir. Bu şekilde ardışık komutların çıktıları dosyada biriktirilebilir.

<br>

### 4.4 Here Documents

- "<<"
- Shell komut dosyalarında ve terminal komutlarında, bir komuta veya betiğe içeriden metin girişi sağlamak için kullanılan bir yönlendirme işlemidir.
- Bu yöntem harici bir dosya kullanmadan çok satırlı metin girişi yapmanızı sağlar.
```
cat << END
This is line 1.
This is line 2.
This is line 3.
END
```
```
output:
     This is line 1.
     This is line 2.
     This is line 3.
```
- Yukarıdaki komutta birden fazla satır END ifadesi gelene kadar input olarak alınır ve cat komutuna aktarılır.

```
grep "keyword" << END
This line contains the keyword.
Another line without the keyword.
END
```
```
output:
     This line contains the keyword.
     Another line without the keyword.
```
- Yukarıdaki komutta END ifadesi gelene kadar girilen ifadeler input olarak grep "keyword" komutuna aktarılır.

```
cat << EOF > deneme.txt
Key1=Value1
Key2=Value2
EOF
```
- Yukarıdaki komut ile EOF ifadesi gelene kadar girilen ifadeler deneme.txt içerisine input olarak aktarılır.


