# Minipipe

## Setup:
1.  ```bash
    git clone https://github.com/aymane5554/minipipe.git minipipe
    ```
2. ```bash
   cd minipipe
   ```
3.  ```bash
    make
    ```
## Usage:
```bash
./pipe inuput_file "cmd args" "cmd args" ... output_file
```
```bash
./pipe here_doc limiter "cmd args" "cmd args" ... output_file
```
## Examples:
```bash
./pipe infile cat "grep hello world" "tr ' ' '\n'" outfile
```
or 
```bash
./pipe here_doc eof "cat" "wc -w" out
```
