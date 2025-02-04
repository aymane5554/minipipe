# Minipipe

## instalation:
1.  clone the repo
2.  ```bash
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
