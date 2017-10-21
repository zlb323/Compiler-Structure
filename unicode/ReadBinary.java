import java.io.*;

public class ReadBinary {

    public static void main(String[] args) throws Exception {
	for (String file : args) {
	    FileInputStream in = new FileInputStream(file);
	    int offset = 0;
	    for (;;) {
		int value = in.read();
		if (value == -1) break;
		System.out.format("offset %4d is %02x\n",offset,value);
		++offset;
	    }
	}
    }

}
