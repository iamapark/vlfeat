function [Fx,Fy] = grad(F,varargin) ;
% GRAD  Gradient
%   [Fx,Fy] = GRAD(F) returns the finite differencies gradient of the
%   function F. The function uses central differencies and for all
%   but the boundaries pixels, for which it uses forward/backward
%   differencies as appropriate.
%
%   GRAD(F,'forward') uses only forward differencies (except on the
%   lower and right boundaries, where backward difference is used).
%   Similarly, GRAD(F,'backward') uses only backward differencies.
%  
%   See also GRADIENT.

type = 'central' ; % forward, backward

for k=1:2:length(varargin)
  switch varargin{k}
    case 'Type'
      type = varargin{k+1} ;
    otherwise
      error(['Parameter ''', varargin{k}, ''' unknown']) ;      
  end
end


[M,N]=size( F ) ;

switch type
  case 'central'
    Fx = [ F(:,2)-F(:,1) , ...
           0.5*(F(:,3:end)-F(:,1:end-2)) , F(:,end)-F(:,end-1) ] ;
    Fy = [ F(2,:)-F(1,:) ; ...
           0.5*(F(3:end,:)-F(1:end-2,:)) ; F(end,:)-F(end-1,:) ] ;
    
  case 'forward'
    Fx = [ F(:,2:end)-F(:,1:end-1) , F(:,end)-F(:,end-1) ] ;
    Fy = [ F(2:end,:)-F(1:end-1,:) ; F(end,:)-F(end-1,:) ] ;
    
  case 'backward'
    Fx = [ F(:,2)-F(:,1) , F(:,2:end)-F(:,1:end-1)] ;
    Fy = [ F(2,:)-F(1,:) ; F(2:end,:)-F(1:end-1,:)] ;
    
  otherwise
    error(['Difference type ''', type, ''' unknown']) ;      
end
