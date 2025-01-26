import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
import java.io.IOException;
import java.io.FileWriter;
import java.io.FileNotFoundException;
//import java.time.LocalDate;
//import java.time.format.DateTimeFormatter;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
//import javax.swing.border.Border;

import javax.swing.JPanel;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;


public class Main extends JFrame implements ActionListener
{

    int BotonPosX = 650;

    int TamañoBotonesY = 35;
    int TamañoBotonesX = 140;

    int EspacioEntreBotones = 50;

    private JFrame frame;

    private JPanel pane;

    private JMenuItem Save, Load;

    private JMenuItem Add, Delete;

    Image image = Toolkit.getDefaultToolkit().getImage("Imagen.jpg");




    public void Main() throws IOException{

        //Creating the Frame
        frame = new JFrame("Object generator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setLayout(null);

       // AddTopBar(frame);

        //AddSideBar(frame);

        AddVisualizer(frame);

        frame.setVisible(true);

        //repaint();
    }
    public void AddTopBar(JFrame frame){

        JMenuBar menuBar = new JMenuBar();

        JMenu MainMenu = new JMenu("Archivo");

        JMenu TaskMenu = new JMenu("Tareas");


        Add = new JMenuItem("Añadir");
        Add.addActionListener(this);
        TaskMenu.add(Add);

        Delete = new JMenuItem("Eliminar");
        Delete.addActionListener(this);
        TaskMenu.add(Delete);


        Save = new JMenuItem("Guardar");
        Save.addActionListener(this);
        MainMenu.add(Save);

        Load = new JMenuItem("Recargar");
        Load.addActionListener(this);
        MainMenu.add(Load);

        menuBar.add(MainMenu);
        menuBar.add(TaskMenu);


        menuBar.setBounds(0,0,800, 45);
        frame.add(menuBar);


    }
    public void AddSideBar(JFrame frame){


        //TODO: Añadir texto aca

        JSpinner Unidades_en_X = new JSpinner(new SpinnerNumberModel(1, 1, 50, 1));
        Unidades_en_X.setBounds(BotonPosX, 1 * EspacioEntreBotones, TamañoBotonesX, 45);
        frame.add(Unidades_en_X);

        //TODO: Añadir texto aca

        JSpinner Unidades_en_Y = new JSpinner(new SpinnerNumberModel(1, 1, 50, 1));
        Unidades_en_Y.setBounds(BotonPosX, 2 * EspacioEntreBotones, TamañoBotonesX, 45);
        frame.add(Unidades_en_Y);


        JButton button_guardar = new JButton("Guardar");
        button_guardar.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                    //Esto es llamado cuando se presiona el boton
            }
        });
        button_guardar.setBounds(BotonPosX,3 * EspacioEntreBotones,TamañoBotonesX, 45);
        frame.add(button_guardar);




    }
    public void AddVisualizer(JFrame frame) throws IOException{




        pane = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                g.drawImage(image, 0, 0, this);
            }
        };
        pane.setLayout(null);
        frame.add(pane);



    }

    //Esto dibuja las unidades
    public void DrawUnits(Graphics g){
        //Dibujar las unidades normales

        //Dibujar las unidades con colision
    }


    public static void main(String[] args) throws IOException{

        Main main = new Main();
        main.Main();

    }



    public void actionPerformed(ActionEvent e) {
        if (e.getSource()==Save) {

        }
        if (e.getSource()==Load) {

        }
        if (e.getSource()==Add) {

        }
        if(e.getSource() == Delete){


        }
    }


}
