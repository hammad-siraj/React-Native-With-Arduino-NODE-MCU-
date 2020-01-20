import React, { Component } from 'react'
import SvgComponent from './svgIcon'
import {
  StyleSheet,
  View,
  Text,
  TouchableOpacity,
  Image
} from 'react-native';

class App extends React.Component {
constructor(){
  super();
  this.state={
  isOpen:false
  }
}



ledController =()=>{
   this.setState({isOpen:true})

 
  fetch(`http://192.168.1.104/LED=ON`)
  .then((res)=>{
   console.log(res)
  fetch(`http://192.168.1.104/LED=ON`).then(()=>
   setTimeout(()=>fetch(`http://192.168.1.104/LED=OFF`).then(()=>this.setState({isOpen:false})),5000))
  
  })

 
    
  
}

  render() {
    const {isOpen}=this.state;
    return (
      <>
      {/* <SvgComponent/> */}
      <View style={styles.header}>
        <Text style={styles.headerText}>COFFEE SHOP</Text>
      </View>
     
      <View style={styles.container}>
        <Text>
          INSTRUCTIONS:
          </Text>
          <Text>
            *PLEASE PUT A CUP TO GET YOUR FAVOURITE COFFEE
          </Text>
      </View>
     
      <View style={styles.image}>
         <Image source={require('./images/coffeeCup.png')} style={{  backgroundColor: '#faf5e4'}}/>
      </View>
     
      <View style={styles.container}>
          <Text >MACHINE IS {`${isOpen? "ON":"OFF"}`}</Text> 
        <TouchableOpacity onPress={this.ledController} style={[styles.button]}>
              <Text style={[styles.text]}>{`TAP HERE TO GET YOUR COFFEE`}</Text>
        </TouchableOpacity>
          
          <Text></Text>    
      </View>
      </>
    )
  }
}


const styles = StyleSheet.create({
 container:{
     flex:1,
     justifyContent:"center",
     alignItems:"center",
     backgroundColor:'#faf5e4'
    
    },
    header:{
      alignItems:"center",
      backgroundColor:'#ff971d',
      height:40
    },
    headerText:{
      fontSize:20,
      fontWeight:"900",
      color:"white",
      fontFamily:"sans-serif-thin",
      textTransform: 'uppercase',
      color: '#FFFFFF',
      
    },
    
    button: {
      display: 'flex',
      height: 50,
      borderRadius: 5,
      justifyContent: 'center',
      alignItems: 'center',

      backgroundColor: '#ff971d',
      shadowColor: '#2AC062',
      shadowOpacity: 0.4,
      shadowOffset: { height: 10, width: 0 },
      shadowRadius: 20,
  },

  text: {
      fontSize: 16,
      textTransform: 'uppercase',
      color: '#FFFFFF',
      fontWeight:"900",
      fontFamily:"sans-serif-thin",
  },
  image:{
    alignItems:"center",
    backgroundColor:'#faf5e4'
  }
});

export default App;
