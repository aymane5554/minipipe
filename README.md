# Minipipe
## Usage:
```bash
./pipe inuput_file "cmd args" "cmd args" ... output_file
```
```bash
./pipe here_doc limiter "cmd args" "cmd args" ... output_file
```
## Example:
```bash
./pipe infile cat "grep hello world" "tr ' ' '\n'" outfile
```
or 
```bash
./pipe here_doc eof "cat" "wc -w" out
```
