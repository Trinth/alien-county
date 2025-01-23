import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
import java.io.IOException;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
import javax.swing.border.Border;


public class Main extends JFrame //implements ActionListener
{

    private JFrame frame;



    public void Main(){

        //Creating the Frame
        frame = new JFrame("Object generator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);

        JMenuBar menuBar = new JMenuBar();

        frame.setVisible(true);

        //InputDialog = new TaskInputDialog(frame,true);



    }

    public static void main(String[] args){

        Main main = new Main();
        main.Main();

    }





}
