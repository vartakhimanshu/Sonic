//
//  ViewController.m
//  Demo
//
//  Created by Philadelphia Game Lab on 6/10/14.
//  Copyright (c) 2014 Philadelphia Game Lab. All rights reserved.

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController
@synthesize Result;
@synthesize count;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    self.Result.text = @"Just Loaded";
    self.count =0;
    self.customAudioUnitInstance = new CustomAudioUnit();
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)click:(id)sender {
    self.count++;
    self.Result.text = [NSString stringWithFormat:@"Clicked %d",self.count];
    self.customAudioUnitInstance->play();
}

- (IBAction)click2:(id)sender {
    self.count+= 2;
    self.Result.text = [NSString stringWithFormat:@"Clicked %d",self.count];
    self.customAudioUnitInstance->stop();
}
@end
