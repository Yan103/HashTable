import re

def process_text(input_file, output_file):
    try:
        with open(input_file, 'r') as f_in:
            text = f_in.read()  

            cleaned_text = re.sub(r'[^a-zA-Z0-9\s]', ' ', text)
            
            words = [word for word in cleaned_text.split() if word]
            
            with open(output_file, 'w') as f_out:
                f_out.write('\n'.join(words))
                
        print(f"Success! Result in: {output_file}")
    
    except FileNotFoundError:
        print("Error! No file!")

process_text('LOR.txt', 'LOR_converted.txt')
