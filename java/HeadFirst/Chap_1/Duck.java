public abstract class Duck{
    FlyBehavior   flyBehavior;
    QuackBehavior quakcBehavior;

    public Duck(){}

    public abstract void display();

    public void performFly(){
        flyBehavior.fly();
    }

    public void performQuakc(){
        quakcBehavior.quack();
    }

    public void Swim(){
        System.out.println("All Duck Float, even decoys!");
    }
}