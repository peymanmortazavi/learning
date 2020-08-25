# Networking in AWS

## Security Groups

Every security group is not only a set of policies that provide inbound and
outbound rules. But it is also a way to provide access to other security groups.

For example, in the context of Kubernetes in AWS. The nodes are actually EC2 instances.
Say we only want to expose 80 and 443 for SSL. Now if we utilize NodePort of a
Service then the master node needs to expose that port and connect to other Pods
to forward requests. Now this becomes a problem, because the security group disallows
anything other than 80. Now, a security group can extend certain access to other
members of the same security group. So I could say security group A exposes 80
to members of security group A. and only 80 to the general traffic.

## Load Balancers

Load Balancers basically take some targets like what EC2 instances or what IP addresses to hit to forward traffic to.
