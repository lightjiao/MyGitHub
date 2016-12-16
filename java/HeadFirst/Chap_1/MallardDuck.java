public class MallardDuck extends Duck{
    
    public MallardDuck(){
        quakcBehavior = new Quack();
        flyBehavior   = new FlyWithWings();
    }

    public void display(){
        System.out.println("I am a MallardDuck");
    }
}